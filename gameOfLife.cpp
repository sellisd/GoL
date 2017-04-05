#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include "gameOfLife.h"
#include "randomv.h"
#include "system.h"

using namespace std;
int gameOfLife::sumN(int i, int j){
  int sumR = 0;
  for(int si = i - 1; si <= i + 1; si++){
    for (int sj = j - 1; sj <= j +1 ; sj++){
      sumR += system::get(si, sj);
    }
  }
  return sumR;
}

void gameOfLife::step(randomv &r){
  //make list of changes and perform them in the end
  vector<pair<int,int> > alive;
  vector<pair<int,int> > dead;
  for(int i = 0; i < system::getSide(); i++){
    for(int j = 0; j < system::getSide(); j++){
      // foreach cell sum 9 surrounding ones
      int stateSum;
      stateSum = sumN(i,j);
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
    system::set(resurectIT->first,resurectIT->second,1);
  }
  for(vector<pair<int,int> >::iterator killIT = dead.begin(); killIT != dead.end(); ++killIT){
    system::set(killIT->first,killIT->second,0);
  }
  system::step(r);
}
