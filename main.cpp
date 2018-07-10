#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <map>
#include <math.h>
#include "randomv.h"
#include "gameOfLife.h"
//#include "lg.h"
#include "ca.h"
#include "entropy.h"
#include "generateStatic.h"

using namespace std;

int main(int argc, char* argv[]){

/*
command line parameters:
side model replicates Tmax by

Options
0:     Gradient
1:     HPP Lattice Gas
2:     Game of Life
3:     Coffee automaton interacting
4:     Coffee automaton non-interacting
5:     Sierpinski's Carpet
6:     square
   */
int x;
int model;
int replicates;
int Tmax;
int byS;
int byW;
int byV;
const char* sfileS = "statistics.dat";
const char* wfileS = "window.dat";
const char* vfileS = "vector.dat";
if(argc == 11){
  x          = atoi(argv[1]); // side
  model      = atoi(argv[2]);
  replicates = atoi(argv[3]);
  Tmax       = atoi(argv[4]);
  byS         = atoi(argv[5]);
  byW         = atoi(argv[6]);
  byV         = atoi(argv[7]);
  sfileS     = argv[8];
  wfileS     = argv[9];
  vfileS     = argv[10];
}else{
  cerr<<"command line parameters:"<<endl;
  cerr<<"side model replicates Tmax byS byW byV soutFileName woutFileName voutFileName"<<endl;
  exit(1);
}
// Initial state variables
double squareFillingProb = 0.9;
int squareSide = x/2;
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
    case 0:{
  /*
           // Smooth gradient
      //initialize grid
      vector<vector<int> > grid;
      for (int i = 0; i < x; i++){
        vector<int> row;
  	    for(int j = 0; j<x; j++){
          row.push_back(0);
  	    }
  	    grid.push_back(row);
      }
      // initialize static library
      generateStatic tables(x);
      tables.gradient(grid,r);
      vector<int> ws;
      vector<int> ss;
      vector<double> k1s;
      vector<double> k2s;
      vector<double> es;
      entropyFunctions.pattern(ws,ss,k1s,k2s,es, grid);
      for(unsigned int i = 0; i<ws.size(); ++i){
        wout<<0<<' '<<ws.at(i)<<' '<<ss.at(i)<<' '<<k1s.at(i)<<' '<<k2s.at(i)<<' '<<es.at(i)<<endl;
      }
      tables.printV(grid, vout);
      */
      break;
    }
    case 2:{         // Game of Life
      gameOfLife g(x);
      g.fillSquare(r, squareSide, squareFillingProb);
      g.run(replicate, Tmax, r, sout, wout, vout, entropyFunctions, byS, byW, byV);
      break;
    }
    case 3:{        // interacting coffee automaton
      ca gasFreeExpansionInteracting(x, true);
      gasFreeExpansionInteracting.fillSquare(r, squareSide, squareFillingProb);
      gasFreeExpansionInteracting.run(replicate, Tmax, r, sout, wout, vout, entropyFunctions, byS, byW, byV);
      break;
    }
    case 4:{        // non-interacting coffee automaton
      ca gasFreeExpansion(x, false);
      gasFreeExpansion.fillSquare(r, squareSide, squareFillingProb);
      gasFreeExpansion.run(replicate, Tmax, r, sout, wout, vout, entropyFunctions, byS, byW, byV);
      break;
    }
    case 5:{         // Sierinski's carpet
    /*
      //initialize grid
      vector<vector<int> > grid;
      for (int i = 0; i < x; i++){
        vector<int> row;
	      for(int j = 0; j<x; j++){
	        row.push_back(0);
	      }
	      grid.push_back(row);
      }
      // initialize static library
      generateStatic tables(x);
      tables.SierpinskiCarpet(grid);
      vector<int> ws;
      vector<int> ss;
      vector<double> k1s;
      vector<double> k2s;
      vector<double> es;
      entropyFunctions.pattern(ws,ss,k1s,k2s,es, grid);
      for(unsigned int i = 0; i<ws.size(); ++i){
      	wout<<0<<' '<<ws.at(i)<<' '<<ss.at(i)<<' '<<k1s.at(i)<<' '<<k2s.at(i)<<' '<<es.at(i)<<endl;
      }
      tables.printV(grid, vout);
      */
      break;
    }case 6:{
        // Square
        /*
      vector<vector<int> > grid;
      for (int i = 0; i < x; i++){
        vector<int> row;
        for(int j = 0; j<x; j++){
          row.push_back(0);
        }
        grid.push_back(row);
      }
      generateStatic tables(x);
      tables.square(grid,squareSide,squareFillingProb, r);
      vector<int> ws;
      vector<int> ss;
      vector<double> k1s;
      vector<double> k2s;
      vector<double> es;
      entropyFunctions.pattern(ws,ss,k1s,k2s,es, grid);
      for(unsigned int i = 0; i<ws.size(); ++i){
        wout<<0<<' '<<ws.at(i)<<' '<<ss.at(i)<<' '<<k1s.at(i)<<' '<<k2s.at(i)<<' '<<es.at(i)<<endl;
      }
      tables.printV(grid, vout);
      */
      break;
    }default:
      exit(1);
    }
  }
  return EXIT_SUCCESS;
}
