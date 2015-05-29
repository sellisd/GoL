#include <iostream>
#include <vector>
#include <map>
#include "ca.h"
#include "randomv.h"
#include "entropy.h"

using namespace std;
ca::ca(void){
  side = 128;
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
  i = abs(i % side);
  j = abs(j % side);
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
// if interacting
//   if different color swap 
//   else pick another and repeat
// if not interacting
//   if selected is not alive pick another and repeat
//   if 1 alive move to second location and add values
//   if multiple alive move only one to second location
  bool success = false;
  while (success != true) {
    int x1 = r.sampleUniformInt(side);
    int y1 = r.sampleUniformInt(side);
    int neighbor = r.sampleUniformInt(4); // 0 1 2 3 = b l u r
    int x2=x1;
    int y2=y1;
    switch(neighbor){
    case 0:
      x2++;
      break;
    case 1:
      y2--;
      break;
    case 2:
      x2--;
      break;
    case 3:
      y2++;
      break;
    default:
      exit(1);
    }
    if(interacting == true){
      if(this->swap(x1,y1, x2,y2)){
      	success = true;
      }
    }else{
      int currentV = this->get(x1,y1);
      int neighborV = this->get(x2,y2);
      if(currentV !=0){
	this->set(x1,y1,currentV-1);
	this->set(x2,y2,neighborV+1);
	success = true;
      }
    }
  }
}



void ca::run(int Tmax, randomv & r, ostream & wout, entropy & entropyFunctions, int by){
  // print and calculate statistics only at by intervals
  for(int t = 0; t < Tmax; t++){
    this->step(r);
    if(t % by == 0){
      map<int,double> Hk;
      entropyFunctions.pattern(Hk, grid);
      for(map<int,double>::iterator it = Hk.begin(); it != Hk.end(); ++it){
        wout<<t<<' '<<(*it).first<<' '<<(*it).second<<endl;
      }
      this->printV();
    }
  }
}

int ca::swap(int x1,int y1, int x2, int y2){
  int a = this->get(x1,y1);
  int b = this->get(x2,y2);
  if(a != b){
    this->set(x1,y1, b);
    this->set(x2,y2,a);
    return 1;
  }else{
    return 0;
  }
}

void ca::printV(void){
  for(int x = 0; x < side; x++){
    for(int y = 0; y < side; y++){
      if(interacting==true){
	cout<<grid.at(x).at(y);
      }else{
	cout<<grid.at(x).at(y)<<' ';
      }
    }
  }
  cout<<endl;
}
