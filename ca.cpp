#include <iostream>
#include <vector>
#include <map>
#include "ca.h"
#include "randomv.h"
#include "entropy.h"

using namespace std;
ca::ca(void){
  side = 64;
  generation = 0;
  this->prepare();
}

ca::ca(int a){
  side = a;
  generation = 0;
  this->prepare();
}

void ca::prepare(void){
  for(int i = 0; i < side; i++){
    vector<int> row; 
    for( int j = 0; j <side; j++){
      row.push_back(0);
    }
    grid.push_back(row);
  }
}

void ca::set(int i, int j, int value){
  i = i % side;
  j = j % side;
  if(i<0){i += side;}
  if(j<0){j += side;}
  grid.at(i).at(j) = value;
}

int ca::get(int i, int j){
  i = i % side;
  j = j % side;
  if(i<0){i += side;}
  if(j<0){j += side;}
  return grid.at(i).at(j);
}

void ca::populateRegion(randomv & r, int window, double p){
  for( int i = (side-window)/2; i <(side-window)/2+window; i++){
    for(int j = (side-window)/2; j <(side-window)/2+window; j++){
      if(r.sampleUniform()<p){
        grid.at(i).at(j) = 1;
      }
    }
  }
}

void ca::step(randomv &r){
  //- coffee automaton lattice rule is random swap two adjacent particles At each time step, choose 2 horizontally or vertically adjacent squares uniformly at random and swap them if they’re colored differentl
// pick one random i
// pick random
//   if different color swap 
//   else pick another and repeat
  bool success = false;
  while (success != true) {
    int x1 = r.sampleUniformInt(side);
    int y1 = r.sampleUniformInt(side);
    int neighbor = r.sampleUniformInt(4); // 0 1 2 3 = b l u r
    int x2=x1;
    int y2=y1;
    switch(neighbor){
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
    if(this->swap(x1,y1, x2,y2)){
    success = true;
    }
  }
}

void ca::run(int Tmax, randomv & r, ostream & wout, ostream & vout, entropy & entropyFunctions, int by){
  // print and calculate statistics only at by intervals
  for(int t = 0; t <= Tmax; t++){
    if(t % by == 0){
      vector<int> ws;
      vector<int> ss;
      vector<double> k1s;
      vector<double> k2s;
      vector<double> es;
      entropyFunctions.pattern(ws,ss,k1s,k2s,es, grid);
      for(unsigned int i = 0; i<ws.size(); ++i){
	wout<<t<<' '<<ws.at(i)<<' '<<ss.at(i)<<' '<<k1s.at(i)<<' '<<k2s.at(i)<<' '<<es.at(i)<<endl;
      }
      this->printV(t, vout);
    }
    this->step(r);
  }
}

int ca::swap(int x1,int y1, int x2, int y2){
  int a = this->get(x1,y1);
  int b = this->get(x2,y2);
  if(a != b){
    this->set(x1,y1,b);
    this->set(x2,y2,a);
    return 1;
  }else{
    return 0;
  }
}

void ca::printV(int t, ostream & vout){
  vout<<t<<' ';
  for(int x = 0; x < side; x++){
    for(int y = 0; y < side; y++){
      vout<<grid.at(x).at(y);
    }
  }
  vout<<endl;
}

int ca::particleNo(vector< vector<int> > & grid){
  int sum = 0;
  for(vector<vector<int> >::iterator it = grid.begin(); it != grid.end(); ++it){
    for(vector<int>::iterator jt = (*it).begin(); jt != (*it).end(); ++jt){
      if((*jt) != 0){
	sum++;
      }
    }
  }
  return sum;
}
