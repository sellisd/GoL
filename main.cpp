#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <map>
#include "randomv.h"
#include "gol.h"
#include "lg.h"

//g++  -Wall -o testing main.cpp  gol.cpp lg.cpp randomv.cpp -lgsl -lgslcblas

using namespace std;
int main(int argc, char* argv[]){
  randomv R;
  lg he(100, 900);
  he.initRegion(R,50,.9);
  he.run(1000);
  exit(0);
  int replicates = 100;
  int x = 128;
  int y = 128;
  ofstream wout;
  ofstream vout;
  wout.open ("window.dat", std::ofstream::out);
  vout.open ("vector.dat", std::ofstream::out);
  for (int replicate = 0; replicate < replicates; replicate++){
    gol sim(x,y);
    randomv r;
    sim.populateRandom(r,0.5*x*y);
  //sim.populateRegion(r, 50, .5);
    sim.run(1000,r,1,wout,vout);
  }
  return EXIT_SUCCESS;
}
