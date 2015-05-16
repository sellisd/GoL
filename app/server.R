
# This is the server logic for a Shiny web application.
# You can find out more about building applications with Shiny here:
#
# http://shiny.rstudio.com
#

library(shiny)
library(entropy)
source("GoLFunctions.R")

shinyServer(
  function(input, output) {
    x <- 50
    y <- 50
    m <- prepareGrid(x,y)
    m <- populateRandom(m,500)
    m <- reactiveValues(x=m) #m$x=2
    s<-reactive({
      m$x<-step(m$x) #m$x=2, m$x=3
    })
    
    observe({
      if (is.null(input$action)){}
      else{
        isolate({
          m$x<-s()#m$x=2
        })
        #print(m$x)
        output$gridPlot <- renderPlot({
          image(m$x,col=c(0,1))
        })
      }
    })
    
  }
)
# shinyServer(
#   function(input, output) {
#     x <- 50
#     y <- 50
#     m <- prepareGrid(x,y)
#     m <- populateRandom(m,500)
#     observeEvent(input$action,{
#       m <- step(m)
#       #m<-m+1
#       output$gridPlot <- renderPlot({
#         image(m,col=c(0,1))
#       })
#       m
#     })
#     output$gridPlot <- renderPlot({image(m,col=c(0,1))})
#   }
# )
