#include <iostream>
#include <vector>
#include "gol.h"
#include "randomv.h"
using namespace std;
gol::gol(void){
  x = 100;
  y = 100;
}

gol::gol(int a){
  x = a;
  y = a;
}

gol::gol(int a, int b){
  x = a;
  y = b;
}
void gol::prepare(){
  for(int i = 0; i < x; i++){
    vector<int> row; 
    for( int j = 0; j <y; j++){
      row.push_back(0);
    }
    m.push_back(row);
  }
}

void gol::set(int i, int j, int value){
  i = abs(i % x);
  j = abs(j % y);
  m.at(i).at(j) = value;
}

int gol::get(int i, int j){
  i = abs(i % x);
  j = abs(j % y);
  return m.at(i).at(j);
}
 
void gol::populateRandom(randomv r, int a){
  // populate random (with resampling though)
  for(int i = 0; i<a; i++){
    int mutateX = r.sampleUniformInt(x);
    int mutateY = r.sampleUniformInt(y);
    m.at(mutateX).at(mutateY) = 1;
  }
}
  
void gol::printM(void){
  for(vector<vector<int> >::iterator it = m.begin(); it != m.end(); ++it){
    for(vector<int>::iterator jt = (*it).begin(); jt != (*it).end(); ++jt){
      cout<<(*jt)<<' ';
    }
    cout<<endl;
  }
}

void gol::run(int T){
  for (int t = 0; t < T; t++){
    this->step();
  }
}

void gol::step(){
  for(int i = 0; i < x; i++){
    for(int j = 0; j < y; j++){
      // foreach cell sum 9 surrounding ones
     int stateSum = this->sumN(i,j);
      if(stateSum == 3){
        this->set(i,j,1);
      }else if(stateSum == 4){
        //keep the same value
      }else{
       this->set(i,j,0);
      }   
    }
  }
}

int gol::sumN(int i, int j){
  int sumR = 0;
  for(int si = i - 1; si < i + 1; si++){
    for (int sj = j - 1; sj < j +1 ; sj++){
      sumR += this->get(si, sj);
    }
  }
  return sumR;
}
