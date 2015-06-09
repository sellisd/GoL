#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include "gol.h"
#include "randomv.h"
using namespace std;
gol::gol(void){
  x = 128;
  y = 128;
  generation = 0;
  this->prepare();
}

gol::gol(int a, int b){
  x = a;
  y = b;
  generation = 0;
  this->prepare();
}

void gol::prepare(){
  //  int debug = 0;
  for(int i = 0; i < x; i++){
    vector<int> row; 
    for( int j = 0; j <y; j++){
      row.push_back(0);
      //      debug++;
    }
    m.push_back(row);
  }
}

void gol::set(int i, int j, int value){
  i = i % x;
  j = j % y;
  if(i<0){i += x;}
  if(j<0){j += y;}
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

void gol::printV(int t, ostream& vout){
  //print as one large vector, one generation per line
  char alive = '1';
  char dead = '0';
  vout<<t<<' ';
  for(vector<vector<int> >::iterator it = m.begin(); it != m.end(); ++it){
    for(vector<int>::iterator jt = (*it).begin(); jt != (*it).end(); ++jt){
      int value = (*jt);
      if(value == 1){
        vout<<alive;
      }else if (value == 0){
        vout<<dead;
      }else{
	cerr<<"problem!";
        exit(1);
      }
    }
  }
  vout<<endl;
}

void gol::vectorizeS(int window, ostream & wout){
  //create vector of submatrix
  //print submatrices of size window as vectors
  //output format
  //generation windowSize windowId vector
  vector<int> bitString;
  int windowId = 0;
  for(int I = 0; I < x; I+=window){
    for(int J = 0; J < y; J+=window){
      wout<<generation<<' ';
      wout<<window<<' ';
      wout<<windowId<<' ';
      for(int i = 0; i < window; i++){
	for(int j = 0; j< window; j++){
	  bitString.push_back(m.at(i+I).at(j+J));
	}
      }
      //      wout<<entropy(bitString);
      windowId++;
      wout<<endl;
    }
  }
}

void gol::populateRandom(randomv & r, int a){
  // populate random (with resampling though)
  for(int i = 0; i<a; i++){
    int mutateX = r.sampleUniformInt(x);
    int mutateY = r.sampleUniformInt(y);
    this->set(mutateX,mutateY,1);
  }
}

void gol::populateRegion(randomv & r, int side, double p){
  //populate a block of size side with density p
  for(int i = (x-side)/2; i < (x-side)/2+side; i++){
    for(int j = (y-side)/2; j < (y-side)/2+side; j++){
      if(r.sampleUniform()<p){
	this->set(i,j,1);
      }
    }
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


void gol::step(randomv &r){
  //make list of changes and perform them in the end
  vector<pair<int,int> > alive;
  vector<pair<int,int> > dead;
  for(int i = 0; i < x; i++){
    for(int j = 0; j < y; j++){
      // foreach cell sum 9 surrounding ones
      int stateSum;
      stateSum = this->sumN(i,j);
      pair<int, int> mIJ(i,j);
      if(stateSum == 3){
        alive.push_back(mIJ);
      }else if(stateSum == 4){       // keep identical
      }else{
        dead.push_back(mIJ);
      }   
    }
  }
  //once the fate of all cells is determined make changes
  for(vector<pair<int,int> >::iterator resurectIT = alive.begin(); resurectIT != alive.end(); ++resurectIT){
    this->set(resurectIT->first,resurectIT->second,1);
  }
  for(vector<pair<int,int> >::iterator killIT = dead.begin(); killIT != dead.end(); ++killIT){
    this->set(killIT->first,killIT->second,0);
  }
  generation++;
}


void gol::run(int T,randomv &r, ostream & wout, ostream & vout, entropy & entropyFunctions, int by){
  for (int t = 0; t < T; t++){
    if(t % by == 0){
      map<int,pair<double,double> > Hk;
      entropyFunctions.pattern(Hk, m);
      for(map<int,pair<double,double> >::iterator it = Hk.begin(); it != Hk.end(); ++it){
        wout<<t<<' '<<(*it).first<<' '<<(*it).second.first<<' '<<(*it).second.second<<endl;
      }
      this->printV(t, vout);
    }
    this->step(r);
  }
}

double gol::density(vector<int> & vectorS){
  int aliveCounter = 0;
  int deadCounter = 0;
  for(vector<int>::iterator it = vectorS.begin(); it != vectorS.end(); ++it){
    if((*it) == 1){
      aliveCounter++;
    }else if ((*it) == 0){
      deadCounter++;
    }else{
      exit(1);
    }
  }
  //frequencies
  double p = double(aliveCounter)/double(vectorS.size());
  return p;
}

