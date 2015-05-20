#include <iostream>
#include <vector>
#include "gol.h"
#include "randomv.h"
using namespace std;
gol::gol(void){
  x = 100;
  y = 100;
  this->prepare();
}

gol::gol(int a, int b){
  x = a;
  y = b;
  this->prepare();
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
  
void gol::printM(void){
  char alive = '1';
  char dead = '0';
  char sep = ' ';
  for(vector<vector<int> >::iterator it = m.begin(); it != m.end(); ++it){
    for(vector<int>::iterator jt = (*it).begin(); jt != (*it).end(); ++jt){
      int value = (*jt);
      if(value == 1){
        cout<<alive<<sep;
      }else if (value == 0){
        cout<<dead<<sep;
      }else{
        exit(1);
      }
    }
    cout<<endl;
  }
  cout<<endl;
}

void gol::printV(void){
  //print as one large vector, one generation per line
  char alive = '1';
  char dead = '0';
  for(vector<vector<int> >::iterator it = m.begin(); it != m.end(); ++it){
    for(vector<int>::iterator jt = (*it).begin(); jt != (*it).end(); ++jt){
      int value = (*jt);
      if(value == 1){
        cout<<alive;
      }else if (value == 0){
        cout<<dead;
      }else{
        exit(1);
      }
    }
  }
  cout<<endl;
}

void gol::printS(int window){
  //print submatrices of size window as vectors
  vector<vector<int> >::iterator it = m.begin();
  vector<int>::iterator jt = (*it).begin();
  for(int i = 0; i < window; i++){
    for(int j = 0; j< window; j++){
      
    }
  }
}

void gol::populateRandom(randomv r, int a){
  // populate random (with resampling though)
  for(int i = 0; i<a; i++){
    int mutateX = r.sampleUniformInt(x);
    int mutateY = r.sampleUniformInt(y);
    this->set(mutateX,mutateY,1);
  }
}

int gol::sumN(int i, int j){
  int sumR = 0;
  for(int si = i - 1; si <= i + 1; si++){
    for (int sj = j - 1; sj <= j +1 ; sj++){
      sumR += this->get(si, sj);
    }
  }
  return sumR;

}


void gol::step(randomv &r, bool useRules){
  //make list of changes and perform them in the end
  vector<pair<int,int> > alive;
  vector<pair<int,int> > dead;
  for(int i = 0; i < x; i++){
    for(int j = 0; j < y; j++){
      // foreach cell sum 9 surrounding ones
      int stateSum;
      if(useRules){
        stateSum = this->sumN(i,j);
      }else{
        //in the random alternative return a random integer from 0 to 9 TODO implement a temperature
        stateSum = r.sampleUniformInt(10);
      }
      pair<int, int> mIJ(i,j);
      if(stateSum == 3){
        alive.push_back(mIJ);
     //   newM.set(i,j,1);
      }else if(stateSum == 4){
       // keep identical
      }else{
        dead.push_back(mIJ);
//        newM.set(i,j,0);
      }   
    }
  }
  //once the fate of all cells is determined make changes
  for(vector<pair<int,int> >::iterator resurectIT = alive.begin(); resurectIT != alive.end(); ++resurectIT){
    this->set(resurectIT->first,resurectIT->second,1);
//    cout<<resurectIT->first<<','<<resurectIT->second<<' ';
  }
  //cout<<endl;

  for(vector<pair<int,int> >::iterator killIT = dead.begin(); killIT != dead.end(); ++killIT){
    this->set(killIT->first,killIT->second,0);
    //cout<<killIT->first<<','<<killIT->second<<' ';
  }
  //cout<<endl;
}


void gol::run(int T,randomv &r, bool useRules){
  for (int t = 0; t < T; t++){
    this->step(r, useRules);
    this->printV();
  }
}
