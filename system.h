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
  int getLogLevel(void) {return logLevel; }
  void setLogLevel(int a){ logLevel = a; }
  int  getSide(void) { return side; }
  void setSide(int a) { side = a; }
  void set(int i, int j, int value);
  int  get(int i, int j);
  void tick(); //! Evolve the system by a single step.
  void gridInit(void); //! initialize system world
  void fillSquare(randomv &r, int a, double p);
  //! Fill a square region of the environmnet.
  /**
  * Fills with 1s a square subregion of the environmnet.
  * @param[in]  r       Instance of random number generator class.
  * @param[in]  window  Side of subregion to be filled in.
  * @param[in]  p       Probability of filling each cell within subregion.
  * @return                      Nothing
  */
  void run(int replicateID, int Tmax,randomv &r, ostream & sout, ostream & wout, ostream & vout, entropy & entropyFunctions, int by);
  //! Run the simulation.
  /**
  * Performs a simulation run and calculates relevant statistics.
  * @param[in]  replicateID      Replicate ID of simulation.
  * @param[in]  Tmax             Run simulations for Tmax steps.
  * @param[in]  r                Random number generation class.
  * @param[out] wout             Statistics on three subgrids.
  * @param[out] wout             Statistics on coarse grained grid.
  * @param[out] vout             Output stream of the state of the system for each generation.
  * @param[in]  entropyFunctions Entropy functions instance
  * @return                      Nothing
  */
  void printV(int t, ostream & vout);
  void makeGrid(vector<vector<int> > & grid);
  virtual void step(randomv &r);
  virtual int randomState(); //! Return a random non-zero state of the cell
 private:
  int side;
  int logLevel;
  vector<vector<int> > grid; //! The world grid
  int generation; // generation or cycle of time evolution
};
#endif
