#include <vector>
#include <iostream>
#include <map>
#include "lg.h"
#include "randomv.h"

lg::randomState(){
    //use byte coding and blur
    //0001: right  :1
    //0010: up     :2
    //0100: left   :4
    //1000: bottom :8
    //Other values are possible before collision resolution
    int direction = rand() % 4; //[0,1,2,3]
    return(2**direction);

}

void lg::to4Byte(int x){

}

int lg::from4Byte(int x){

}

void lg::step(void){
  //scan and move each particle towards its direction
  //resolve collisions
  for(int i = 0; i < system::getSide(); i++){
    for(int j = 0; j < system::getSide(); j++){
      int d = system::get(i,j);

    }
  }
  system::step(r);
/*  //initialize lattice1
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
  */
}
