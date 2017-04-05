# find linear region with good fit
goodFit<-function(x,y,minXpoints=10,r2=.95){
  found <- 0
  maxR <- 0
  slope <- 0
  slopeP  <- 0
  slopeSE <- 0
  intercept <- 0
  keep <- 1
  r <- sort(unique(x))
  for(range in c(minXpoints:length(unique(x)))){
    if(length(r)-range == 0){
      windows <- 1
    }else{
      windows <- c(1:(length(r)-range))
    }
    for(i in windows){
      index <- which(x>=r[i] & x<=r[i+range-1])
      s <- lm(y[index]~x[index])
      rsq <- summary(s)$r.squared
      if(rsq <r2){
        next;
      }
      if(maxR < rsq){ #compare to previous maximum
        maxR = rsq
        slope <- summary(s)$coefficients[2,1]
        intercept <- summary(s)$coefficients[1,1]
        slopeP <- summary(s)$coefficients[2,4]
        slopeSE <- summary(s)$coefficients[2,2]
        keep <- index
        found <- 1
      }
    }
  }
  if(found == 0){
    return("NA")
  }else{
    return(list("index" = keep,"r2"=maxR,"slope"=slope, "p.value"=slopeP, "intercept"=intercept, "se" = slopeSE))
  }
}

evolutionStats <- function(wdat){
  # calculate statistics at each generation during the evolution of a system
  # INPUT: .w.dat files
  # OUTPUT: returns matrices with medians and quantiles for H, K1 and K2
  generations <- unique(wdat$V1)
  windows <- unique(wdat$V2)
  mm.H <- matrix(ncol=length(windows),nrow=length(generations))
  ml.H <- matrix(ncol=length(windows),nrow=length(generations))
  mu.H <- matrix(ncol=length(windows),nrow=length(generations))
  mm.K1 <- matrix(ncol=length(windows),nrow=length(generations))
  ml.K1 <- matrix(ncol=length(windows),nrow=length(generations))
  mu.K1 <- matrix(ncol=length(windows),nrow=length(generations))
  mm.K2 <- matrix(ncol=length(windows),nrow=length(generations))
  ml.K2 <- matrix(ncol=length(windows),nrow=length(generations))
  mu.K2 <- matrix(ncol=length(windows),nrow=length(generations))
  generationCounter <- 1
  for(g in generations){
    windowCounter <- 1
    for(w in windows){
      av.H <- wdat[which(wdat$V1==g & wdat$V2==w),6] #, 6 for Entropy
      qs.H <- quantile(av.H,probs=c(0.1,0.5,0.9),names=FALSE)
      mm.H[generationCounter,windowCounter] <- qs.H[2]
      ml.H[generationCounter,windowCounter] <- qs.H[1]
      mu.H[generationCounter,windowCounter] <- qs.H[3]
      av.K1 <- wdat[which(wdat$V1==g & wdat$V2==w),4] #, 4 K_PNG
      qs.K1 <- quantile(av.K1,probs=c(0.1,0.5,0.9),names=FALSE)
      mm.K1[generationCounter,windowCounter] <- qs.K1[2]
      ml.K1[generationCounter,windowCounter] <- qs.K1[1]
      mu.K1[generationCounter,windowCounter] <- qs.K1[3]
      av.K2 <- wdat[which(wdat$V1==g & wdat$V2==w),5] #, 5 for K_RLE
      qs.K2 <- quantile(av.K2,probs=c(0.1,0.5,0.9),names=FALSE)
      mm.K2[generationCounter,windowCounter] <- qs.K2[2]
      ml.K2[generationCounter,windowCounter] <- qs.K2[1]
      mu.K2[generationCounter,windowCounter] <- qs.K2[3]
      windowCounter <- windowCounter + 1
    }
    generationCounter <- generationCounter + 1
  }  
  list("generations" = generations,
       "Hmedian"     = mm.H,
       "Hlower"      = ml.H,
       "Hupper"      = mu.H,
       "K1median"    = mm.K1,
       "K1lower"     = ml.K1,
       "K1upper"     = mu.K1,
       "K2median"    = mm.K2,
       "K2lower"     = ml.K2,
       "K2upper"     = mu.K2)
}


#' Plot box counting dimension regression
#'
#' @param wout 
#'
#' @return
#' @export
#'
#' @examples
plotScalc <- function(wout){
  # plot S for static structures (0 generations)
  N <- log(wout$V3,base=10)
  w <- log(1/wout$V2,base=10)
  Lfit <- goodFit(w,N,minXpoints = 4, r2 = 0.9)
  plot(w,N,xlab="log2(1/w)", ylab="log2(N(S))",pch=19)
  m <- min(w[Lfit$index])
  M <- max(w[Lfit$index])
  segments(m,m*Lfit$slope+Lfit$intercept,M,M*Lfit$slope+Lfit$intercept)
  l <- sprintf("%2.2f",Lfit$slope)
  p <- sprintf("%2.2e",Lfit$p.value)
  r <- sprintf("%2.2e",Lfit$r2)
  legend("topleft", paste("slope: ",l,", p. value: ",p,", r^2: ", r, sep=""))
}


plotSTcalc <- function(wout){
  # plot S vs time
  generations <- unique(wout$V1)
  windows <- unique(wout$V2)
  generationCounter <- 1
  D <- vector()
  DSE <- vector()
  Dr2 <- vector()
  counter <- 1
  for(g in generations){
    N <- log(wout$V3[wout$V1==g],base=10)
    w <- log(1/wout$V2[wout$V1==g],base=10)
    Lfit <- goodFit(w,N,minXpoints = 4, r2 = 0.9)
    D[counter]   <- Lfit$slope
    DSE[counter] <- Lfit$se
    Dr2[counter] <- Lfit$r2
    counter <- counter + 1
  }
  data.frame("generations" = generations,
             "D"          = D,
             "DSE"        = DSE,
             "Dr2"        = Dr2)
}


#' Vector to matrix format transformation.
#' 
#' Given a vector the space matrix is returned
#'
#' @param vectorS numerical or character vector
#' @param side    size of square
#'
#' @return side x side numeric matrix
#' @export
#'
#' @examples:
#' a <- read.table("~/projects/GoL/caNI100.v.dat", nrows = 100)
#' image(vector2matrix(v=as.vector(unlist(a[14,c(2:length(a))])), side = 64))
vector2matrix <- function(vectorS, side){
  matrix(vectorS, nrow = side, byrow = TRUE)
}

#' Coarse Grain matrix.
#'
#' @param window int : size of non-overlapping windows for coarse grainning
#' @param gridM matrix: matrix
#'
#' @return coarse grained matrix with summs 
#' @export
#'
#' @examples
coarseGrain <- function(window, gridM){
  #non overlapping windows without error check, x and y should be powers of 2
  coarseGrained <- numeric(0)
  for(I in seq(from = 1, to = nrow(gridM) - 1, window)){
    for(J in seq(from = 1, to = ncol(gridM) - 1, window)){
      sum <-  0
      counter <- 0
      for(i in seq(from = 1, to = window - 1, by = 1)){
        for(j in seq(from = 1, to = window - 1, by = 1)){
          sum <- sum + gridM[(i+I),(j+J)]
          counter <- counter + 1;
        }
      }
      coarseGrained <- append(coarseGrained, sum);
    }
  }
  coarseGrained
}

#' Plot an image of the model at time t
#'
#' @param vectorFile
#' 
#' @param t  time
#'
#' @return
#' @export
#'
#' @examples
plotState <- function(vectorFile, side, t){
  a <- read.table(vectorFile)
  image(vector2matrix(vectorS = as.vector(unlist(a[t, c(2:length(a))])), side = side))
}
