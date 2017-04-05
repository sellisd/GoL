#ifndef CA_H
#define CA_H
#include <vector>
#include <fstream>
#include "randomv.h"
#include "entropy.h"
#include "system.h"

using namespace std;

/**
 * Interactng coffee automaton
 */

class ca : public system{
  public:
    ca(void);
    ca(int side){};
    void step(randomv &r); //! Extend base class step
    int  swap(int x1, int y1, int x2, int y2);
};
#endif
