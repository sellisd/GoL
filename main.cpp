#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <map>
#include "randomv.h"
#include "gol.h"
#include "lg.h"
#include "entropy.h"

//g++  -Wall -o testing main.cpp entropy.cpp gol.cpp lg.cpp randomv.cpp -lgsl -lgslcblas

using namespace std;
int main(int argc, char* argv[]){
  int x = 128;
  int y = 128;
  entropy entropyFunctions(x,y);
  ofstream wout;
  ofstream vout;
  wout.open ("window.dat", std::ofstream::out);
  vout.open ("vector.dat", std::ofstream::out);
  int replicates = 1;
  randomv r;
  for (int replicate = 0; replicate < replicates; replicate++){
    /*
      HPP Lattice Gass
     */
    lg he(x, 900);
    he.setIgnoreCollisions(true);
    he.initRegion(r,50,.9);
    he.run(1000, wout, entropyFunctions);
    /*Game of Life
    gol sim(x,y);
    sim.populateRandom(r,0.5*x*y);
    sim.run(1000,r,1,wout,vout,entropyFunctions);
    */
  }
  return EXIT_SUCCESS;
}
