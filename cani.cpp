#include <iostream>
#include <vector>
#include <map>
#include "cani.h"
#include "randomv.h"
#include "entropy.h"

cani::cani(void){
  side = 64;
}

cani::cani(int a){
  side = a;
}

void cani::populateRegion(randomv &r, int window, double p){
  for( int i = (side-window)/2; i <(side-window)/2+window; i++){
    for(int j = (side-window)/2; j <(side-window)/2+window; j++){
      if(r.sampleUniform()<p){
        x.push_back(i);
        y.push_back(j);
      }
    }
  }
}

void cani::step(randomv &r){
  for(int i = 0; i<x.size(); i++){
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

void cani::printV(int t, ostream & vout){
  // Create vector of size side*side filled with 0
  vout<<t<<' ';
  vector<int> vectorS(side*side,0);
  for(int i = 0; i< x.size(); ++i){
    vector<int>::iterator it = vectorS.begin();
    it+=(x.at(i) + side*y.at(i));
    (*it)++;
  }
  for (std::vector<int>::iterator i = vectorS.begin(); i != vectorS.end(); ++i){
    vout<<(*i)<<' ';
  }
  vout<<endl;
}

void cani::run(int Tmax,randomv &r, ostream & wout, ostream & vout, entropy & entropyFunctions, int by){
  for(int t = 0; t <= Tmax; ++t){
    if(t % by == 0){
      vector<int> ws;
      vector<int> ss;
      vector<double> k1s;
      vector<double> k2s;
      vector<double> es;
      vector<vector<int> > grid;
      this->makeGrid(grid);
      entropyFunctions.pattern(ws,ss,k1s,k2s,es, grid);
      for(unsigned int i = 0; i<ws.size(); ++i){
        wout<<t<<' '<<ws.at(i)<<' '<<ss.at(i)<<' '<<k1s.at(i)<<' '<<k2s.at(i)<<' '<<es.at(i)<<endl;
      }
      this->printV(t, vout);
    }
  //  cerr<<this->x.size()<<' ';
    this->step(r);
  //  cerr<<this->x.size()<<endl;
  }
}

void cani::makeGrid(vector<vector<int> > & grid){
  // Create vector of size side*side filled with 0
  vector<int> vectorS(side*side,0);
  for(int i = 0; i< x.size(); ++i){
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
