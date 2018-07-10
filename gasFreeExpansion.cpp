#include <iostream>
#include <vector>
#include <map>
#include "cani.h"
#include "randomv.h"
#include "entropy.h"
#include "system.h"

void cani::step(randomv &r){
  for(unsigned int i = 0; i<x.size(); i++){
    int x2 = x.at(i);
    int y2 = y.at(i);
    int direction = r.sampleUniformInt(4); // 0 1 2 3 : b l u r
    switch(direction){
    case 0:{
      x2++;
      break;}
    case 1:{
      y2--;
      break;}
    case 2:{
      x2--;
      break;}
    case 3:{
      y2++;
      break;}
    default:
      exit(1);
    }
    this->move(i,x2,y2);
  }
}

void cani::move(int i, int x2, int y2){
  x2 = x2 % side;
  y2 = y2 % side;
  if(x2<0){x2 += side;}
  if(y2<0){y2 += side;}
  x.at(i) = x2;
  y.at(i) = y2;
}
/**
* Create a vector of particles
* @param[in] i   Particle index (order in vector).
* @param[in] x2  x-axis coordinate of new particle location.
* @param[in] y2  y-axis coordinate of new particle location.
* @return              Nothing
*/

void cani::makeGrid(vector<vector<int> > & grid){
  // Create vector of size side*side filled with 0
  vector<int> vectorS(side*side,0);
  for(unsigned int i = 0; i< x.size(); ++i){
    vector<int>::iterator it = vectorS.begin();
    it+=(x.at(i) + side*y.at(i));
    (*it)++;
  }
  //make grid from vector to use with entropyFunctions
  for(int i = 0; i < side; i++){
    vector<int> row;
    for( int j = 0; j <side; j++){
      row.push_back(vectorS.at(i+j*side));
    }
    grid.push_back(row);
  }
}
