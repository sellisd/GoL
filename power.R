#Power analysis for entropy estimation
library(entropy)
# window side cells replicates
side <- c(2,4,8,16,32,64)
df <- data.frame(side=side, stringLength = side^2, stringNo = 64^2/side^2)
eMLDF       <- data.frame(side=side,lower=NA,median=NA,upper=NA)
eMMDF       <- data.frame(side=side,lower=NA,median=NA,upper=NA)
eJeffreysDF <- data.frame(side=side,lower=NA,median=NA,upper=NA)
eLaplaceDF  <- data.frame(side=side,lower=NA,median=NA,upper=NA)
eSGDF       <- data.frame(side=side,lower=NA,median=NA,upper=NA)
eminimaxDF  <- data.frame(side=side,lower=NA,median=NA,upper=NA)
eCSDF       <- data.frame(side=side,lower=NA,median=NA,upper=NA)
eshrinkDF   <- data.frame(side=side,lower=NA,median=NA,upper=NA)  

repeats <- 100
for(i in c(1:length(side))){
  eML       <- vector()
  eMM       <- vector()
  eJeffreys <- vector()
  eLaplace  <- vector()
  eSG       <- vector()
  eminimax  <- vector()
  eCS       <- vector()
  eshrink   <- vector()  
  counter <- 1  
  for(j in c(1:(repeats*df$stringNo[i]))){
    vectorSize <- df$stringLength[i]
    vector <- sample(c(0,1),vectorSize,replace=TRUE)
    eML[counter]       <- entropy(table(vector), unit="log2",method="ML")
    eMM[counter]       <- entropy(table(vector), unit="log2",method="MM")
    eJeffreys[counter] <- entropy(table(vector), unit="log2",method="Jeffreys")
    eLaplace[counter]  <- entropy(table(vector), unit="log2",method="Laplace")
    eSG[counter]       <- entropy(table(vector), unit="log2",method="SG")
    eminimax[counter]  <- entropy(table(vector), unit="log2",method="minimax")
    eCS[counter]       <- entropy(table(vector), unit="log2",method="CS")
    eshrink[counter]   <- entropy(table(vector), unit="log2",method="shrink")
    counter <- counter + 1
  }  
#  hist(eML,main=df$side[i])
#  hist(eMM,main=df$side[i])
#  hist(eJeffreys,main=df$side[i])
#  hist(eLaplace,main=df$side[i])
#  hist(eSG,main=df$side[i])
#  hist(eminimax,main=df$side[i])
#  hist(eCS,main=df$side[i])
#  hist(eshrink,main=df$side[i])
  eMLDF[i,]       <- c(df$side[i],quantile(eML,probs=c(0.25,0.5,0.75),names = FALSE))
  eMMDF[i,]       <- c(df$side[i],quantile(eMM,probs=c(0.25,0.5,0.75),names = FALSE))
  eJeffreysDF[i,] <- c(df$side[i],quantile(eJeffreys,probs=c(0.25,0.5,0.75),names = FALSE))
  eLaplaceDF[i,]  <- c(df$side[i],quantile(eLaplace,probs=c(0.25,0.5,0.75),names = FALSE))
  eSGDF[i,]       <- c(df$side[i],quantile(eSG,probs=c(0.25,0.5,0.75),names = FALSE))
  eminimaxDF[i,]  <- c(df$side[i],quantile(eminimax,probs=c(0.25,0.5,0.75),names = FALSE))
  eCSDF[i,]       <- c(df$side[i],quantile(eCS,probs=c(0.25,0.5,0.75),names = FALSE))
  eshrinkDF[i,]   <- c(df$side[i],quantile(eshrink,probs=c(0.25,0.5,0.75),names = FALSE))
}
save(eMLDF,eMMDF,eJeffreysDF,eLaplaceDF,eSGDF,eminimaxDF,eCSDF,eshrinkDF,file="~/projects/GoL/power.dat")