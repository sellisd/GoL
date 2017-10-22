#ifndef ENTROPY_H
#define ENTROPY_H

using namespace std;
/**
 * Entropy calculations
 */
class entropy{
 public:
  entropy(void);
  entropy(int x, int y);
  double log2(double x);
  void   hist(map<int,double> &, vector<int> & vectorS);
  double infEntropy(map<int,double> & hist);
  void   coarseGrain(vector<int> & coarseGrained, int window, vector<vector<int> > & grid);
  void   pattern(vector<int> & ws, vector<int> & ss, vector<double> & k1s, vector<double> & k2s, vector<double> & es, vector<vector<int> > & grid);
  double compress(vector<int> & vectorS);
  double compressPNG(vector<int> & vectorS, unsigned int window);
  int    boxCount(vector<int> & vectorS);
  void extractSubGrid(vector<vector<int> > & grid, vector<int> subgrid, int width, int x, int y)
    //! Extract a square region of the grid.
    /**
    * Extracts a square region of the grid and returns it
    * as a one dimensional vector.
    * @param grid the grid of the systm.
    * @param subgrid the extracted square.
    * @param width the side of the square to extract.
    * @param x row index of top-left corner of subgrid
    * @param y column index of top-left corner of subgrid
    */
  pair<double,double> cornerComplexity(vector<vector<int> > & grid, int cornerWidth /*= 8*/);
 private:
  int x;
  int y;
};
#endif
