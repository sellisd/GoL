#ifndef CANI_H
#define CANI_H
#include <vector>
#include <fstream>
#include "randomv.h"
#include "entropy.h"
#include "system.h"

using namespace std;

/**
 * Gass free expansion
 * Particles randomly drift moving at each step either horizontally or
 * vertically
 */

class cani : public system{
 public:
  //! Default constructor
  cani(void);
  //! Constructor with side
  cani(int side){};
  /**
  * One time step (generation), extends the base class step.
  * @param[in] randomv   Random number generation class.
  * @return              Nothing
  */
  void step(randomv &r);
  /**
  * Move particle i at location (x2,y2).
  * @param[in] i   Particle index (order in vector).
  * @param[in] x2  x-axis coordinate of new particle location.
  * @param[in] y2  y-axis coordinate of new particle location.
  * @return              Nothing
  */
  void move(int i, int x2, int y2);
  void makeGrid(vector<vector<int> > & grid);
 private:
  //! Total number of particles
  int N;
  //! x-axis coordinate of particles
  vector<int> x;
  //! y-axis coordinate of particles
  vector<int> y;
};
#endif
