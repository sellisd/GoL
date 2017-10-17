#ifndef SYSTEM_h
#define SYSTEM_h
#include <vector>
#include "randomv.h"
#include "entropy.h"

using namespace std;

/**
* Abstract system
*/

class system{
public:
  system(void);
  system(int side);
  int  getSide(void) { return side; }
  void setSide(int a) { side = a; }
  void set(int i, int j, int value);
  int  get(int i, int j);
  void tick();
  void gridInit(void); //! initialize system world
  void fillSquare(randomv &r, int a, double p);
  void run(int T,randomv &r, ostream & wout, ostream & vout, entropy & entropyFunctions, int by);
  void printV(int t, ostream & vout);
  void makeGrid(vector<vector<int> > & grid);
  virtual void step(randomv &r);
  virtual int randomState(); //! Return a random non-zero state of the cell
 private:
  int side;
  vector<vector<int> > grid; //! The world grid
  int generation; // generation or cycle of time evolution
};
#endif
