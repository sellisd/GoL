#ifndef CA_H
#define CA_H
#include <vector>
#include <fstream>
#include "randomv.h"
#include "entropy.h"

using namespace std;

/**
 * coffee automaton
 */

class ca{
 public:
  ca(void);
  ca(int side);
  int getSide(void)  { return side; }
  void setSide(int a) { side = a; }
  void prepare(void); //initialize
  void set(int i, int j, int value);
  int get(int i, int j);
  void populateRegion(randomv & r, int a, double p);
  void step(randomv &r);
  void run(int T,randomv &r, ostream & wout, entropy & entropyFunctions, int by);
  int swap(int x1, int y1, int x2, int y2);
  void printV(void);
  void setInteracting(bool i) { interacting = i; } 
 private:
  int side;
  vector< vector<int> > grid;
  bool interacting;
  int generation;
};
#endif
