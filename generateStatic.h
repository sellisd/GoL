#ifndef GENERATESTATIC_H
#define GENERATESTATIC_H
#include "randomv.h"

using namespace std;
/**
* Generate static matrices
 */

class generateStatic{
  public:
    generateStatic(void);
    generateStatic(int side);
    void gradient(vector<vector<int> > & grid, randomv & r);
    void filled(vector<vector<int> > & grid);
    void square(vector<vector<int> > & grid, int window, double p, randomv &r);
    void printMatrix(vector<vector<int> > & grid);
    void SierpinskiCarpet(vector<vector<int> > & grid);
    int  isSierpinskiCarpetPixelFilled(int x, int y);
    void printV(vector<vector<int> > & grid, ofstream & vout);
  private:
  int side;
 };
#endif
