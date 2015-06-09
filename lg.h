#ifndef LG_H
#define LG_H
#include <fstream>
#include "randomv.h"
#include "entropy.h"
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
  lg(int a);
  void setSide(int a){ side = a; }
  int  getSide(void){ return side; }
  void step(void);
  void initRand(randomv &r, int N);
  void run(int Tmax,ostream & wout, entropy & entropyFunctions, int by);
  void printV(void);
  void initRegion(randomv &r, int window, double p);
  void lattice2grid(vector<vector<int> > & grid);
  void setIgnoreCollisions(bool a){ ignoreCollisions = a; }
 private:
  int side; // box side
  vector<vector<vector<int> > > lattice; //x.y.<0:botom.1:left.2:up.3:right>
  vector<int> direction; //direction
  vector<pair<int, int> > coordinates; 
  bool ignoreCollisions;
 };
#endif
