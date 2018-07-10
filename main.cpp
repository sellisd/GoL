#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <map>
#include <math.h>
#include "randomv.h"
#include "gameOfLife.h"
#include "gasFreeExpansionI.h"
#include "gasFreeExpansion.h"
#include "entropy.h"

using namespace std;

int main(int argc, char* argv[]){

/*
command line parameters:
side model replicates Tmax by

Options
1:     Game of Life
2:     Gas free expansion with interactions
3:     Gas free expansion
   */
int x;
int model;
int replicates;
int Tmax;
int byS;
int byW;
int byV;
const char* sfileS = "../data/statistics.dat";
const char* wfileS = "../data/window.dat";
const char* vfileS = "../data/vector.dat";
if(argc == 11){
  x           = atoi(argv[1]); // side
  model       = atoi(argv[2]);
  replicates  = atoi(argv[3]);
  Tmax        = atoi(argv[4]);
  byS         = atoi(argv[5]);
  byW         = atoi(argv[6]);
  byV         = atoi(argv[7]);
  sfileS      = argv[8];
  wfileS      = argv[9];
  vfileS      = argv[10];
}else{
  cerr<<"command line parameters:"<<endl;
  cerr<<"side model replicates Tmax byS byW byV soutFileName woutFileName voutFileName"<<endl;
  exit(1);
}
// Initial state variables
double  squareFillingProb = 0.9;
int     squareSide        = x/2;
entropy entropyFunctions(x, x);
ofstream sout;
ofstream wout;
ofstream vout;
sout.open (sfileS, std::ofstream::out);
wout.open (wfileS, std::ofstream::out);
vout.open (vfileS, std::ofstream::out);
randomv r;
for (int replicate = 0; replicate < replicates; replicate++){
  switch(model){
    case 1:{         // Game of Life
      gameOfLife g(x);
      g.fillSquare(r, squareSide, squareFillingProb);
      g.run(replicate, Tmax, r, sout, wout, vout, entropyFunctions, byS, byW, byV);
      break;
    }
    case 2:{        // Gas free expansion with interactions
      gasFreeExpansionI gasFreeExpansionInteracting(x);
      gasFreeExpansionInteracting.fillSquare(r, squareSide, squareFillingProb);
      gasFreeExpansionInteracting.run(replicate, Tmax, r, sout, wout, vout, entropyFunctions, byS, byW, byV);
      break;
    }
    case 3:{        // Gas free expansion
      gasFreeExpansion gasFreeExpansion(x);
      gasFreeExpansion.fillSquare(r, squareSide, squareFillingProb);
      gasFreeExpansion.run(replicate, Tmax, r, sout, wout, vout, entropyFunctions, byS, byW, byV);
      break;
    }default:
      exit(1);
    }
  }
  return EXIT_SUCCESS;
}
