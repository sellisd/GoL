#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <map>
#include "randomv.h"
#include "gol.h"
#include "lg.h"
#include "ca.h"
#include "entropy.h"
#include <limits>

//g++  -Wall -o run main.cpp entropy.cpp gol.cpp lg.cpp ca.cpp randomv.cpp lodepng.cpp -lgsl -lgslcblas
using namespace std;

int main(int argc, char* argv[]){
/*
command line parameters:
side model replicates Tmax by

examples: 
single generation gradient:
./run 64 0 1 1 1
Non-interacting ca
./run 64 4 100 1000 10
Interacting ca
./run 64 3 100 10000 100
Game of Life
./run 64 2 100 1000 10
Lattice Gas
./run 64 1 100 1
*/
  /*Options
0:     Gradient
1:     HPP Lattice Gas
2:     Game of Life
3:     Coffee automaton interacting
4:     Coffee automaton non-interacting
   */
  if(argc==6){
    int x          = atoi(argv[1]); // side
    int model      = atoi(argv[2]);
    int replicates = atoi(argv[3]);
    int Tmax       = atoi(argv[4]);
    int by         = atoi(argv[5]);
  }else{
    cerr<<"command line parameters:"<<endl;
    cerr<<"side model replicates Tmax by"<<endl;
    exit(1);
  }
  int y = x;
  entropy entropyFunctions(x,y);
  ofstream wout;
  ofstream vout;
  wout.open ("window.dat", std::ofstream::out);
  vout.open ("vector.dat", std::ofstream::out);
  randomv r;
  for (int replicate = 0; replicate < replicates; replicate++){
    switch(model){
      case 0:          // Smooth gradient
        vector<vector<int> > grid;
        for (int i = 0; i < x; i++){
          vector<int> row;
          for(int j = 0; j<y; j++){
            if(double(i)/double(x) < r.sampleUniform()){
              row.push_back(0);
            }else{
              row.push_back(1);
            }
          }
          grid.push_back(row);
        }
        map<int,double> Hk;
        entropyFunctions.pattern(Hk, grid);
        for(map<int,double>::iterator it = Hk.begin(); it != Hk.end(); ++it){
          cout<<' '<<(*it).first<<' '<<(*it).second<<endl;
        }
        break;
      case 1:         // HPP Lattice Gass
        lg he(x);
        he.setIgnoreCollisions(true);
        he.initRegion(r,25,.9);
        he.run(Tmax, wout, entropyFunctions, by);
        break;
      case 2:         // Game of Life  
        gol sim(x,y);
        sim.populateRegion(r,25,0.9);
        sim.run(Tmax,r,wout,vout,entropyFunctions, by);
        break;
      case 3:        // interacting coffee automaton
        ca cappuccino(x);
        cappuccino.setInteracting(true);
        cappuccino.populateRegion(r,25,.9);
        cappuccino.run(Tmax,r, wout, entropyFunctions, by);
        break;
      case 4:        // non-interacting coffee automaton
        ca cappuccino(x);
        cappuccino.setInteracting(false);
        cappuccino.populateRegion(r,25,.9);
        cappuccino.run(Tmax,r, wout, entropyFunctions, by);      
        break;
      default:
        exit(1);
    }
  }
  return EXIT_SUCCESS;
}
