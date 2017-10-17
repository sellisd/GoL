#ifndef LG_H
#define LG_H
#include <fstream>
#include "randomv.h"
#include "entropy.h"
#include "system.h"

using namespace std;
/**
 * Lattice Gass, HPP model
 N  particles in a box of side x. Each particle has a corresponding direction of
 movement (bottom, left, up, right) and moves one cell per time. Only one
 particle of each direction fits in a cell of the lattice
 collision resolution:
   - head on collision -> perpendicular
   - 90 degrees -> reflection == no interaction (all particles are identical,
     thus they just exchange places)
 */

class lg : public system{
 public:
  lg(void);
  lg(int a){};
  void step(randomv &r);
  
  void lattice2grid(vector<vector<int> > & grid);
  void setIgnoreCollisions(bool a){ ignoreCollisions = a; }
  int randomSate(void);
 private:
  vector<vector<bitset<4> > > grid;
  vector<vector<vector<int> > > lattice; //x.y.<0:botom.1:left.2:up.3:right>
  vector<int> direction; //direction
  vector<pair<int, int> > coordinates;
  bool ignoreCollisions;
 };
#endif
