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