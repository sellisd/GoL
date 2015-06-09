#ifndef GOL_H
#define GOL_H
#include <vector>
#include <fstream>
#include <map>
#include "randomv.h"
#include "entropy.h"

using namespace std;
/**
 * Game of Life on flat 2D torus grid
 */
class gol{
 public:
  gol(void);
  gol(int a, int b);
  int getX(void)  { return x; }
  int getY(void)  { return y; }
  void setX(int a) { x = a; }
  void setY(int a) { y = a; }
  void prepare(void); //initialize
  void printM(void);
  void printV(int t, ostream & vout);
  void vectorizeS(int window, ostream & wout);
  void set(int i, int j, int value);
  int get(int i, int j);
  vector< vector<int> > getM(void){ return m;}
  void setM(vector<vector<int> > a){ m = a;}
  void populateRandom(randomv & r, int a);
  void populateRegion(randomv & r, int a, double p);
  int sumN(int i, int j);
  void step(randomv &r);
  void run(int T,randomv &r, ostream & wout, ostream & vout, entropy & entropyFunctions, int by);
  double density(vector<int> & vectorS);
 private:
  int x; //!< number of rows
  int y; //!< number of columns
  vector< vector<int> > m;
  int generation;
};
#endif
