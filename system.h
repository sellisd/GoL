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
  //! Default constructor
  system(void);
  //! Constructor with system side
  system(int side);
  //! Get side of system's world
  int  getSide(void) { return side; }
  //! Set side of system's world
  void setSide(int a) { side = a; }
  /**
  * Set value of cell i,j in systems world
  * @param[in] i      x-axis coordinate.
  * @param[in] j      y-axis coordinate.
  * @param[in] value  Value to set cell i,j.
  * @return              Nothing
  */
  void set(int i, int j, int value);
  /**
  * Get value of cell i,j in systems world
  * @param[in] i      x-axis coordinate.
  * @param[in] j      y-axis coordinate.
  * @return    int    Value of cell i,j
  */
  int  get(int i, int j);
  //! Evolve the system by a single step.
  void tick();
  //! initialize system world
  void gridInit(void);
  //! Fill a square region of the environmnet.
  /**
  * Fills with 1s a square subregion of the environmnet.
  * @param[in]  r       Instance of random number generator class.
  * @param[in]  window  Side of subregion to be filled in.
  * @param[in]  p       Probability of filling each cell within subregion.
  * @return                      Nothing
  */
  void fillSquare(randomv &r, int a, double p);
  //! Run the simulation.
  /**
  * Performs a simulation run and calculates relevant statistics.
  * @param[in]  replicateID      Replicate ID of simulation.
  * @param[in]  Tmax             Run simulations for Tmax steps.
  * @param[in]  r                Random number generation class.
  * @param[out] sout             Statistics on three subgrids.
  * @param[out] wout             Statistics on coarse grained grid.
  * @param[out] vout             Output stream of the state of the system for each generation.
  * @param[in]  byS              Log sout every byS generations.
  * @param[in]  byW              Log wout every byS generations.
  * @param[in]  byV              Log vout every byS generations.
  * @param[in]  entropyFunctions Entropy functions instance
  * @return                      Nothing
  */
  void run(int replicateID, int Tmax, randomv & r, ostream & sout, ostream & wout, ostream & vout, entropy & entropyFunctions, int byS, int byW, int byV);
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
