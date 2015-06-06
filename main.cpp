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

//g++  -Wall -o testing main.cpp entropy.cpp gol.cpp lg.cpp ca.cpp randomv.cpp lodepng.cpp -lgsl -lgslcblas
using namespace std;

int main(int argc, char* argv[]){

  /*Options
0:     Gradient
1:     HPP Lattice Gas
2:     Game of Life
3:     Coffee automaton interacting
4:     Coffee automaton non-interacting
   */
  int x = 64;
  int y = 64;
  entropy entropyFunctions(x,y);
  ofstream wout;
  ofstream vout;
  wout.open ("window.dat", std::ofstream::out);
  vout.open ("vector.dat", std::ofstream::out);
  int replicates = 100;
  randomv r;
  for (int replicate = 0; replicate < replicates; replicate++){
    /**       Smooth gradient
     *
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
    */

    /* coffee automaton
     */
    ca cappuccino(x);
    cappuccino.setInteracting(false);
    cappuccino.populateRegion(r,25,.9);
    cappuccino.run(1000,r, wout, entropyFunctions, 10);
    /*
      HPP Lattice Gass
    lg he(x, 900);
    he.setIgnoreCollisions(true);
    he.initRegion(r,50,.9);
    he.run(1000, wout, entropyFunctions);
    */
    /*Game of Life
    gol sim(x,y);
    //sim.populateRandom(r,0.5*x*y);
    sim.populateRegion(r,50,0.9);
    sim.run(1000,r,1,wout,vout,entropyFunctions);
    */
  }
  return EXIT_SUCCESS;
}
