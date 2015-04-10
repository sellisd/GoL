prepareGrid <- function(x,y){
  m <- matrix(0,nrow=x,ncol=y)
}

populateRandom <- function(m,r){
  x <- nrow(m)
  y <- ncol(m)
  m[sample(x*y,r,replace=FALSE)] <- 1  
  m
}

run <- function(m,t,plotBool){
  for(i in c(1:t)){
    mn <- step(m)
    if(sum(mn)==0){
      break
    }
    if(sum(mn)==1){
      break
    }
    if(all(mn == m)){
      break
    }
    if(plotBool == TRUE){
      e10 <- matrix(nrow=x,ncol=y)
      for(ei in c(1:x)){
        for(ej in c(1:y)){
          e10[ei,ej] <- vectorizePattern(m,ei,ej,6)    
        }
      }
      image(e10,main=i)
      image(mn,col=c("#00000000",1),add=TRUE)
    }
    m <- mn
  }
  mn
}

step <- function(m){
  x <- nrow(m)
  y <- ncol(m)
  md <- matrix(nrow=nrow(m),ncol=ncol(m)) #copy table
  #for each cell summ surrounding 9 states
  for(i in c(1:x)){
    for(j in c(1:y)){
      stateSum <- sumN(m,i,j)
      if(stateSum == 3){
        md[i,j] <- 1
      }else if(stateSum == 4){
        md[i,j] <- m[i,j]
      }else{
        md[i,j] <- 0
      }
    }
  }
  md
}

sumN <- function(m,i,j){
  #calculate the sum of 9 cells surrounding (i,j)
  x <- nrow(m)
  y <- ncol(m)
  sumR <- 0
  for(ci in c((i-1):(i+1))){
    for(cj in c((j-1):(j+1))){
      if(ci < 1){
        ci <- x
      }
      if(cj < 1){
        cj <- y
      }
      if(ci > x){
        ci <- 1
      }
      if(cj > y){
        cj <- 1
      }
      sumR <- sumR + m[ci,cj]
    }
  }
  sumR
}

x <- 20
y <- 20
m <- prepareGrid(x,y)
m <- populateRandom(m,10)
image(m,col=c(0,1))
m <- run(m,50,1)
library(entropy)

nrow(e10)
hist(e10)

vectorizePattern <- function(m,i,j,w){
  #calculate the entropy around point i,j with a window of size w
  x <- nrow(m)
  y <- ncol(m)
  r <- floor(w/2)
  # build vector and calculate block entropy?
  s <- numeric(r*r)
  counter <- 1
  for(ci in c((i-r):(i+r))){
    celli <- ci
    if(ci < 1){
      celli <- x + ci
    }
    for(cj in c((j-r):(j+r))){
      cellj <- cj
      if(cj < 1){
        cellj <- y + cj
      }
      if(ci > x){
        celli <- ci - x
      }
      if(cj > y){
        cellj <- cj - y
      }
     # print(paste(celli,cellj,ci,cj,r))
      s[counter] <- m[celli,cellj]
      counter <- counter+1
    }
  }
  entropy(s)
}

m[100,12]
y
