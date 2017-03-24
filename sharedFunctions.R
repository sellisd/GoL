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