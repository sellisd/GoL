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
    void printMatrix(vector<vector<int> > & grid);
    void SierpinskiCarpet(vector<vector<int> > & grid);
    int  isSierpinskiCarpetPixelFilled(int x, int y);
  private:
  int side;
 };
#endif
