library(seqinr) #s2c

#' Vector to matrix format transformation.
#' 
#' Given a vector the space matrix is returned
#'
#' @param vectorS numerical or character vector
#' @param side    size of square
#' @param type    ["string"|"vector"] of integers
#'
#' @return side x side numeric matrix
#' @export
#'
#' @examples:
#' a <- read.table("~/projects/GoL/caNI100.v.dat", nrows = 100)
#' image(vector2matrix(v=as.vector(unlist(a[14,c(2:length(a))])), side = 64,type = "vector"))
vector2matrix <- function(vectorS, type, side){
  if (type == "string"){
    vectorS <- as.numeric(s2c(vectorS))
  }else if (type == "vector"){
    # pass
  }else{
    warning(paste("Unknown type", type))
  }
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
