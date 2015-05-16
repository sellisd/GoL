#include <iostream>
#include <cstdlib>
#include "randomv.h"
#include "gol.h"

//g++ -Wall -o testing main.cpp gol.cpp  randomv.cpp -lgsl -lgslcblas

using namespace std;
int main(int argc, char* argv[]){
  int x = 30;
  int y = 30;
  gol torus(x,y);
  randomv r;
  torus.prepare();
  torus.printM();
  torus.populateRandom(r,x*y/2);
  torus.printM();
  torus.step();
  torus.printM();
	       //prepare grid
  //#make a grid objsect
  return EXIT_SUCCESS;
}
/*
 
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
	      */
