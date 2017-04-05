#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H
#include <vector>
#include <fstream>
#include <map>
#include "randomv.h"
#include "entropy.h"
#include "system.h"

using namespace std;
/**
 * Game of Life on flat 2D torus grid
 */
class gameOfLife : public system{
 public:
  int sumN(int i, int j);
  void applyRules(randomv &r);
 private:
};
#endif
