#ifndef LG_H
#define LG_H
#include "randomv.h"
using namespace std;
/**
 * Lattice Gass, HPP model
 N  particles in a box of side x
 each particle has a corresponding direction of movement (bottom, left, up, right) and moves one cell per time
 only one particle of each direction fits in a cell of the lattice
 collision resolution:
   - head on collision -> perpendicular
   - 90 degrees -> no interaction (they exchange places but they are identical)
 */

class lg{
 public:
  lg(void);
  lg(int a, int b);
  void setSide(int a){ side = a; }
  int getSide(void){ return side; }
  void setN(int a){ N = a; }
  int getN(void){ return N; }
  void step(void);
  void initRand(randomv &r);
  void run(int Tmax);
  void printV(void);
  void initRegion(randomv &r, int window, double p);
 private:
  int side; // box side
  int N; // number of particles
  vector<vector<vector<int> > > lattice; //x.y.<0:botom.1:left.2:up.3:right>
  vector<int> direction; //direction
  vector<pair<int, int> > coordinates; 
 };
#endif
