#include <vector>
#include <iostream>
#include <map>
#include "lg.h"
#include "randomv.h"

using namespace std;
lg::lg(void){
  exit(0); // do not use default values
}


lg::lg(int a){
  side = a;
  for(int x = 0; x < side; x++){
    vector<vector<int> > row;
    for(int y = 0; y < side; y++){
      vector<int> particle (4,0);
      row.push_back(particle);
    }
    lattice.push_back(row);
  }
}

void lg::initRand(randomv & r, int N){
  for(int i = 0; i < N; i++){
    int x = r.sampleUniformInt(side);
    int y = r.sampleUniformInt(side);
    int directionI = r.sampleUniformInt(4);
    for(int j = 0; j < 4; j++){
      if(j == directionI){
	lattice.at(x).at(y).at(j) = 1;
      }else{
	lattice.at(x).at(y).at(j) = 0;
      }
    }
  }
}


void lg::initRegion(randomv & r, int window,double p){
  for( int i = (side-window)/2; i <(side-window)/2+window; i++){
    for(int j = (side-window)/2; j <(side-window)/2+window; j++){
      if(r.sampleUniform()<p){
      	int directionI = r.sampleUniformInt(4);
	      for(int z = 0; z < 4; z++){
          if(z == directionI){
	          lattice.at(i).at(j).at(z) = 1;
	        }else{
	          lattice.at(i).at(j).at(z) = 0;
	        }
	      }
      }
    }
  }
}

void lg::step(void){
  //initialize lattice1
  vector<vector<vector<int> > > lattice1; 
  for(int x = 0; x < side; x++){
    vector<vector<int> > row;
    for(int y = 0; y < side; y++){
      vector<int> particle (4,0);
      row.push_back(particle);
    }
    lattice1.push_back(row);
  }
  //calculate new positions and populate lattice 1
  for(int i = 0; i < side; i++){
    for(int j = 0; j < side; j++){
      if(lattice.at(i).at(j).at(0) == 1 ){ // moving down
	if( i == side - 1){
	  // inject on top
	  lattice1.at(0).at(j).at(0) = 1;
	}else{ // move down
	  lattice1.at(i+1).at(j).at(0) = 1;
	}
      }else{
	//	lattice1.at(i).at(j).at(0) = 0;
      }
      if(lattice.at(i).at(j).at(1) == 1){ // moving left
	if( j == 0){
	  // inject on right
	  lattice1.at(i).at(side - 1).at(1) = 1;
	}else{ //move left
	  lattice1.at(i).at(j-1).at(1) = 1;
	}
      }else{
	//	lattice1.at(i).at(j).at(0) = 0;
      }
      if(lattice.at(i).at(j).at(2) == 1){ // moving up
	if( i == 0 ){
	  // inject bellow
	  lattice1.at(side - 1).at(j).at(2) = 1;
	}else{
	  // move up
	  lattice1.at(i-1).at(j).at(2) = 1;
	}
      }else{
	//	lattice1.at(i).at(j).at(0) = 0;
      }
      if(lattice.at(i).at(j).at(3) == 1){ // moving right
	if( j == side - 1){
          // inject on left
          lattice1.at(i).at(0).at(3) = 1;
	}else{
          // move right
          lattice1.at(i).at(j+1).at(3) = 1;
        }
      }else{
	//	lattice1.at(i).at(j).at(0) = 0;
      }
    }
  }
  if(ignoreCollisions == true){
  }else{
    //resolve collisions in lattice 1
    for(int i = 0; i < side; i++){
      for(int j = 0; j < side; j++){
	bool vertical = false;
	bool horizontal = false;
	if(lattice1.at(i).at(j).at(0) == 1 and lattice1.at(i).at(j).at(2) == 1){
	  // vertical head collision
	  vertical = true;
       }
	if(lattice1.at(i).at(j).at(1) == 1 and lattice1.at(i).at(j).at(3) == 1){
	  // horizontal head collision
	  horizontal = true;
	}
	if(vertical == true and horizontal == true){
	  // do nothing, particles are interchangeable
       }else if(vertical == true and horizontal == false){
	  lattice1.at(i).at(j).at(0) = 0;
	  lattice1.at(i).at(j).at(1) = 1;
	  lattice1.at(i).at(j).at(2) = 0;
	  lattice1.at(i).at(j).at(3) = 1;
	}else if(vertical == false and horizontal == true){
	  lattice1.at(i).at(j).at(0) = 1;
	  lattice1.at(i).at(j).at(1) = 0;
	 lattice1.at(i).at(j).at(2) = 1;
	 lattice1.at(i).at(j).at(3) = 0;
	}else{
	  // both false
	}
      }
    } 
  }
  //copy lattice 1 back to lattice 0 and repeat
  lattice = lattice1;  
}

void lg::run(int Tmax, ostream & wout, ostream & vout, entropy & entropyFunctions, int by){
  for(int t = 0; t <= Tmax; t++){
    if(t % by == 0){
      vector<vector<int> > grid; //grid to populate with snapshot of lattice
      this->lattice2grid(grid);
      vector<int> ws;
      vector<int> ss;
      vector<double> k1s;
      vector<double> k2s;
      vector<double> es;
      entropyFunctions.pattern(ws,ss,k1s,k2s,es, grid);
      for(unsigned int i = 0; i<ws.size(); ++i){
	wout<<ws.at(i)<<' '<<ss.at(i)<<' '<<k1s.at(i)<<' '<<k2s.at(i)<<' '<<es.at(i)<<endl;
      }
      this->printV(t, vout);
    }
    this->step();
  }
}

void lg::printV(int t, ostream & vout){
  vout<<t<<' ';
  for(int x = 0; x < side; x++){
    for(int y = 0; y < side; y++){
      int particleNo = 0;
      for(int z = 0; z < 4; z++){
      	if (lattice.at(x).at(y).at(z) == 1){
	  particleNo++;
	}
      }
      vout<<particleNo;
    }
  }
  vout<<endl;
}

void lg::lattice2grid(vector<vector<int> > & grid){
  for(int x = 0; x < side; x++){
    vector<int> row;
    for(int y = 0; y < side; y++){
      int presence = 0;
      for(int z = 0; z < 4; z++){
        if(lattice.at(x).at(y).at(z)!=0){
          presence = 1;
        }
      }
      row.push_back(presence);
    }
    grid.push_back(row);
  }
}
