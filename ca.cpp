#include <iostream>
#include <vector>
#include <map>
#include "ca.h"
#include "randomv.h"
#include "entropy.h"
#include "system.h"

using namespace std;

void ca::step(randomv &r){
  //- coffee automaton lattice rule is random swap two adjacent particles At each time step, choose 2 horizontally or vertically adjacent squares uniformly at random and swap them if they’re colored differentl
// pick one random i
// pick random
//   if different color swap
//   else pick another and repeat
// if non-interacting always swap
  bool success = false;
  while (success != true) {
    int x1 = r.sampleUniformInt(system::getSide());
    int y1 = r.sampleUniformInt(system::getSide());
    int neighbor = r.sampleUniformInt(4); // 0 1 2 3 = b l u r
    int x2=x1;
    int y2=y1;
    switch(neighbor){
    case 0:{
      x2++;
      break;
    }case 1:{
      y2--;
      break;
    }case 2:{
      x2--;
      break;
    }case 3:{
      y2++;
      break;
    }default:
      exit(1);
    }
    if(swap(x1,y1, x2,y2)){
      success = true;
    }
  }
  system::step(r);
}

int ca::swap(int x1,int y1, int x2, int y2){
  int a = system::get(x1,y1);
  int b = system::get(x2,y2);
  if(interacting == false){//if non interacting always swap
    system::set(x1,y1,b);
    system::set(x2,y2,a);
    return 1;
  }else{
    //else check
    if(a != b){
      system::set(x1,y1,b);
      system::set(x2,y2,a);
      return 1;
    }else{
      return 0;
    }
  }
}
