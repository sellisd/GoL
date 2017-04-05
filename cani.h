#ifndef CANI_H
#define CANI_H
#include <vector>
#include <fstream>
#include "randomv.h"
#include "entropy.h"
#include "system.h"

using namespace std;

/**
 * Non-interacting coffee automaton
 */

class cani : public system{
 public:
  cani(void);
  cani(int side){};
  void step(randomv &r);
  void move(int i, int x2, int y2);
  void makeGrid(vector<vector<int> > & grid);
 private:
  int N; //number of praticles
  vector<int> x; //coordinates
  vector<int> y;
};
#endif
