#ifndef CANI_H
#define CANI_H
#include <vector>
#include <fstream>
#include "randomv.h"
#include "entropy.h"

using namespace std;

/**
 * Non-interacting coffee automaton
 */

class cani{
 public:
  cani(void);
  cani(int side);
  void prepare(void); //initialize
  void populateRegion(randomv & r, int a, double p);
  void step(randomv &r);
  void run(int T,randomv &r, ostream & wout, ostream & vout, entropy & entropyFunctions, int by);
  void printV(int t, ostream & vout);
  void move(int i, int x2, int y2);
  void makeGrid(vector<vector<int> > & grid);
 private:
  int side;
  int N; //number of praticles
  vector<int> x; //coordinates
  vector<int> y;
};
#endif
