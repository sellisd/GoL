library(seqinr) #s2c

#' Vector to matrix format transformation.
#' 
#' Given a vector the space matrix is returned
#'
#' @param vectorS numerical or character vector
#' @param side    size of square
#' @param type    ["string"|"vector"] of integers
#'
#' @return
#' @export
#'
#' @examples
vector2matrix <- function(vectorS, type, side){
  if (type == "string"){
    v <- as.numeric(s2c(vectorS))
  }else if (type == "vector"){
    # pass
  }else{
    warning(paste("Unknown type", type))
  }
  matrix(v, nrow = side, byrow = TRUE)
}