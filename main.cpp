#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <map>
#include <math.h>
#include "randomv.h"
#include "gol.h"
#include "lg.h"
#include "ca.h"
#include "entropy.h"
#include "cani.h"
#include "generateStatic.h"

//g++  -Wall -o run main.cpp entropy.cpp gol.cpp lg.cpp ca.cpp cani.cpp generateStatic.cpp randomv.cpp lodepng.cpp -lgsl -lgslcblas
using namespace std;

int main(int argc, char* argv[]){
  //  int value = 255*255; //[1
  //  int div = ceil(double(value)/255.);
  //  cerr<<div<<' '<<value-255*(div-1)<<endl;
  //  exit(0);
/*
command line parameters:
side model replicates Tmax by

examples: 
single generation gradient:
./run 64 0 1 1 1 gradient.w.dat gradient.v.dat
Non-interacting ca
./run 64 4 100 1000 10 caNI.w.dat caNI.v.dat
Interacting ca
./run 64 3 100 10000 100 caI.w.dat caI.v.dat
Game of Life
./run 64 2 100 1000 10 gol.w.dat gol.v.dat
Lattice Gas
./run 64 1 100 1 lg.w.dat lg.v.dat
*/
  /*Options
0:     Gradient
1:     HPP Lattice Gas
2:     Game of Life
3:     Coffee automaton interacting
4:     Coffee automaton non-interacting
5:     Sierpinski's Carpet
   */
  int x;
  int model;
  int replicates;
  int Tmax;
  int by;
  const char* wfileS = "window.dat";
  const char* vfileS = "vector.dat";
  if(argc==8){
    x          = atoi(argv[1]); // side
    model      = atoi(argv[2]);
    replicates = atoi(argv[3]);
    Tmax       = atoi(argv[4]);
    by         = atoi(argv[5]);
    wfileS     = argv[6];
    vfileS     = argv[7];
  }else{
    cerr<<"command line parameters:"<<endl;
    cerr<<"side model replicates Tmax by window vector"<<endl;
    exit(1);
  }
  int y = x;
  entropy entropyFunctions(x,y);
  ofstream wout;
  ofstream vout;
  wout.open (wfileS, std::ofstream::out);
  vout.open (vfileS, std::ofstream::out);
  randomv r;
  for (int replicate = 0; replicate < replicates; replicate++){
    switch(model){
    case 0:{          // Smooth gradient
      //initialize grid
      vector<vector<int> > grid;
      for (int i = 0; i < x; i++){
	vector<int> row;
	for(int j = 0; j<y; j++){
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
      break;
    }
    case 1:{         // HPP Lattice Gass
      lg he(x);
      he.setIgnoreCollisions(true);
      he.initRegion(r,25,.9);
      he.run(Tmax, wout, vout, entropyFunctions, by);
      break;
    }
    case 2:{         // Game of Life  
      gol sim(x,y);
      sim.populateRegion(r,25,0.9);
      sim.run(Tmax,r,wout,vout,entropyFunctions, by);
      break;
    }
    case 3:{        // interacting coffee automaton
      ca cappuccino(x);
      cappuccino.populateRegion(r,25,.9);
      cappuccino.run(Tmax,r, wout, vout, entropyFunctions, by);
      break;
    }
    case 4:{        // non-interacting coffee automaton
      cani late(x);
      late.populateRegion(r,25,.9);
      vector<vector<int> > grid;
      late.run(Tmax,r, wout, vout, entropyFunctions, by);      
      break;
    }
    case 5:{         // Sierinski's carpet
      //initialize grid
      vector<vector<int> > grid;
      for (int i = 0; i < x; i++){
	vector<int> row;
	for(int j = 0; j<y; j++){
	  row.push_back(0);
	}
	grid.push_back(row);
      }
      // initialize static library
      generateStatic tables(x);
      //    tables.printMatrix(grid);
      vector<int> ws;
      vector<int> ss;
      vector<double> k1s;
      vector<double> k2s;
      vector<double> es;
      entropyFunctions.pattern(ws,ss,k1s,k2s,es, grid);
      for(unsigned int i = 0; i<ws.size(); ++i){
	wout<<0<<' '<<ws.at(i)<<' '<<ss.at(i)<<' '<<k1s.at(i)<<' '<<k2s.at(i)<<' '<<es.at(i)<<endl;
      }
      break;
    }default:
      exit(1);
    }
  }
  return EXIT_SUCCESS;
}
