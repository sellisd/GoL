#include <vector>
#include <iostream>
#include "randomv.h"
#include "generateStatic.h"
using namespace std;
generateStatic::generateStatic(void){
  side = 64;
}

generateStatic::generateStatic(int x){
  side = x;
}

void generateStatic::gradient(vector<vector<int> > & grid, randomv & r){
  for (int i = 0; i < side; ++i){
    for(int j = 0; j < side; ++j){
      if(double(i)/double(side) < r.sampleUniform()){
	grid.at(i).at(j) = 0;
      }else{
	grid.at(i).at(j) = 1;
      }
    }
  }
}
 

void generateStatic::SierpinskiCarpet(vector<vector<int> >& grid){
  //side of the grid should be 3^n for a full centered carpet
  int x = 0;
  for(vector<vector<int> >::iterator i = grid.begin(); i != grid.end(); ++i){
    int y = 0;
    for(vector<int>::iterator j = (*i).begin(); j != (*i).end(); ++j){
      grid.at(x).at(y) = this->isSierpinskiCarpetPixelFilled(x,y);
      y++;
    }
    x++;
  }
}

int generateStatic::isSierpinskiCarpetPixelFilled(int x, int y){
  // code adapted from http://en.wikipedia.org/wiki/Sierpinski_carpet
  while(x>0 || y>0) // when either of these reaches zero the pixel is determined to be on the edge 
    // at that square level and must be filled
    {
      if(x%3==1 && y%3==1){ //checks if the pixel is in the center for the current square level
	return 0;
      }
      x /= 3; //x and y are decremented to check the next larger square level
      y /= 3;
    }
  return 1; // if all possible square levels are checked and the pixel is not determined 
  // to be open it must be filled
}

void generateStatic::printMatrix(vector<vector<int> > & grid){
  for(vector<vector<int> >::iterator i = grid.begin(); i != grid.end(); ++i){
    for(vector<int>::iterator j = (*i).begin(); j != (*i).end(); ++j){
      if((*j) == 1){
	cout<<'#'<<' ';
      }else{
	cout<<' '<<' ';
      }
    }
    cout<<endl;
  }
  cout<<endl;
}
