prepareGrid <- function(x,y){  # function that creates a matrix. Each cell of the matrix corresponds to a cell in the grid
  m <- matrix(0,nrow=x,ncol=y)
}

populateRandom <- function(m,r){ # function that randomly makes some cells "alive"
  x <- nrow(m)
  y <- ncol(m)
  m[sample(x*y,r,replace=FALSE)] <- 1  
  m
}

run <- function(m,t,plotBool){ # function that iterates the game of life t steps and draws the plot at each step
  a <- numeric(t)
  b <- numeric(t)
  d <- numeric(t)
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
    e <- calcEntropy(m,6)
    b[i] <- mean(e,na.rm=TRUE)
    a[i] <- entropy(c(m))
    d[i] <- sum(m)
    if(plotBool == TRUE){
      image(e,main=i)
      image(mn,col=c("#00000000",1),add=TRUE)
    }
    m <- mn
  }
  list(mn,a,b,d)
}

calcEntropy <- function(m,r){  # function taht calculate the local entropy around each cell taking into account r cells around it
  x <- nrow(m)
  y <- ncol(m)
  e <- matrix(nrow=x,ncol=y)
  for(ei in c(1:x)){
    for(ej in c(1:y)){
      e[ei,ej] <- vectorizePattern(m,ei,ej,r)    
    }
  }
  e
}

step <- function(m){ # function that calculates the state of the simulation after one time step (which cells die etc)
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

sumN <- function(m,i,j){  # function that calculates the sum of cells surrounding cell i,j
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



# a simple run of the simulation
library(entropy)
x <- 50
y <- 50
m <- prepareGrid(x,y)
m <- populateRandom(m,500)
image(m,col=c(0,1))
l <- run(m,50,1)
#matplot(data.frame(l[[2]]/log(l[[4]]),l[[3]]),type="o",pch=19)
#matplot(data.frame(l[[2]],l[[3]]),type="o",pch=19)
#legend("topright",c("all","window"),col=c(1,2),lty=1,pch=19,bty="n")


# entropy vs density
ed <- numeric()
for(i in seq(from=1,to=2500,by=10)){
  m <- prepareGrid(x,y)
  m <- populateRandom(m,i)
  ed <- append(ed,entropy(c(m)))
}



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
