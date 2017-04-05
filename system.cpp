#include <iostream>
#include <vector>
#include <map>
#include "system.h"
#include "randomv.h"
#include "entropy.h"

system::system(void){
  side = 64;
  generation = 0;
  this->gridInit();
}

system::system(int a){
  side = a;
  generation = 0;
  this->gridInit();
}

void system::gridInit(void){
  for(int i = 0; i < side; i++){
    vector<int> row;
    for( int j = 0; j <side; j++){
      row.push_back(0);
    }
    grid.push_back(row);
  }
}

void system::set(int i, int j, int value){
  i = i % side;
  j = j % side;
  if(i<0){i += side;}
  if(j<0){j += side;}
  grid.at(i).at(j) = value;
}

int system::get(int i, int j){
  i = i % side;
  j = j % side;
  if(i<0){i += side;}
  if(j<0){j += side;}
  return grid.at(i).at(j);
}

void system::fillSquare(randomv & r, int window, double p){
  for( int i = (side-window)/2; i <(side-window)/2+window; i++){
    for(int j = (side-window)/2; j <(side-window)/2+window; j++){
      if(r.sampleUniform()<p){
        this->set(i, j, 1);
      }
    }
  }
}

void system::tick(){
  cout<<"in system::tick"<<endl;
  generation++;
}

void system::step(randomv &r){
  cout<<"in system::step"<<endl;
  tick();
}

void system::run(int Tmax, randomv & r, ostream & wout, ostream & vout, entropy & entropyFunctions, int by){
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
      printV(t, vout);
    }
    step(r);
  }
}

void system::printV(int t, ostream & vout){
  vout<<t<<' ';
  for(int x = 0; x < side; x++){
    for(int y = 0; y < side; y++){
      vout<<this->get(x, y)<<' ';
    }
  }
  vout<<endl;
}
