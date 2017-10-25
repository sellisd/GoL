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

int system::randomState(void){
  return(1);
}

void system::fillSquare(randomv & r, int window, double p){
  for( int i = (side-window)/2; i <(side-window)/2+window; i++){
    for(int j = (side-window)/2; j <(side-window)/2+window; j++){
      if(r.sampleUniform()<p){
        this->set(i, j, randomState());
      }
    }
  }
}

void system::tick(void){
  generation++;
}

void system::step(randomv &r){
  tick();
}

void system::run(int replicateID, int Tmax, randomv & r, ostream & sout, ostream & wout, ostream & vout, entropy & entropyFunctions, int by){
/*
extractsubgrids 3
and for each calculate statistics
coarsegrain
and calculate statistics
*/
sout<<"replicate"<<"\t"
    <<"generation"<<"\t"
    <<"Ktl"<<"\t"
    <<"Kce"<<"\t"
    <<"Kbr"<<"\t"
    <<"Htl"<<"\t"
    <<"Hce"<<"\t"
    <<"Hbr"<<"\t"
    <<"Dtl"<<"\t"
    <<"Dce"<<"\t"
    <<"Dbr"<<endl;
wout<<"replicate"<<"\t"
    <<"generation"<<"\t"
    <<"window"<<"\t"
    <<"K"<<"\t"
    <<"H"<<endl;
for(int t = 0; t <= Tmax; t++){
  if(t % by == 0){
    //statistics //printW
    vector<double> topleftStats;
    vector<double> centerStats;
    vector<double> bottomrightStats;
    map<int, vector<double> > cgStats;
    entropyFunctions.subGridStats(grid, topleftStats, centerStats, bottomrightStats);
    entropyFunctions.coarseGrainedStats(grid, cgStats);
    sout<<replicateID<<"\t"
        <<t<<"\t";
    for(int i = 0; i < 3; i++){
      sout<<topleftStats[i]<<"\t"
          <<centerStats[i]<<"\t"
          <<bottomrightStats[i]<<"\t";
    }
    sout<<endl;
    for(map<int, vector<double> >::iterator it = cgStats.begin(); it != cgStats.end(); it++){
      wout<<replicateID<<"\t"
          <<t<<"\t"
          <<(*it).first<<"\t"; //window
      for(vector<double>::iterator jt = (*it).second.begin(); jt != (*it).second.end(); jt++){
          wout<<(*jt)<<"\t";
      }
      wout<<endl;
    }
    printV(t, vout);
  }
  step(r);
}
/*
if(logLevel == 1){
    cout<<"time"<<"\t"
        <<"Stopleft"<<"\t"
        <<"Scenter"<<"\t"
        <<"Ktopleft"<<"\t"
        <<"Kcenter"<<"\t"
        <<"Htopleft"<<"\t"
        <<"Hcenter"<<"\t"
        <<"density"<<endl;
  }
  for(int t = 0; t <= Tmax; t++){
    if(t % by == 0){
      vector<int> ws;
      vector<int> ss;
      vector<double> k1s;
      vector<double> k2s;
      vector<double> es;
      cout<<t<<"\t";
      entropyFunctions.pattern(ws,ss,k1s,k2s,es, grid);
      if(logLevel == 1){
        cout<<t<<"\t";
  //      entropyFunctions.subGridPattern(grid);
      }
      cout<<"LL"<<t<<endl;
      for(unsigned int i = 0; i<ws.size(); ++i){
	       wout<<t<<' '<<ws.at(i)<<' '<<ss.at(i)<<' '<<k1s.at(i)<<' '<<k2s.at(i)<<' '<<es.at(i)<<endl;
      }
      printV(t, vout);
    }
    step(r);
  }
  */
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
