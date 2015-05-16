#ifndef GOL_H
#define GOL_H
#include "randomv.h"
#include <vector>
using namespace std;
/**
 * Game of Life class.
 */
class gol{
 public:
  gol(void);
  gol(int a);
  gol(int a, int b);
  int getX(void)  { return x; }
  int getY(void)  { return y; }
  void setX(int a) { x = a; }
  void setY(int a) { y = a; }
  void prepare(void); //initialize
  void populateRandom(randomv r, int a);
  void printM(void);
  void set(int i, int j, int value);
  int get(int i, int j);
  void step();
  int sumN(int i, int j);
  void run(int T);
 private:
  int x; //!< number of rows
  int y; //!< number of columns
  vector< vector<int> > m;
};
#endif
