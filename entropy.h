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
  void   extractSubGrid(vector<vector<int> > & grid, vector<int> & subgrid, int width, int x, int y);
  //! Extract a square region of the grid.
  /**
  * Extracts a square region of the grid and returns it
  * as a one dimensional vector.
  * @param[in]  grid     Grid of the systm.
  * @param[out] subgrid  Extracted square.
  * @param[in]  width    Side of the square to extract.
  * @param      x        Row index of top-left corner of subgrid
  * @param      y        Column index of top-left corner of subgrid
  * @return              Nothing
  */
  void   subGridPattern(vector<vector<int> > & grid);
  //! Statistics of two subgrids.
  /**
  * Calculate statistics at two subgrids: top left corner and center.
  * coarse graining window sizes.
  * @param[in]  grid     Grid of the system.
  * @return              Nothing
  */
  void   pattern(vector<int> & ws, vector<int> & ss, vector<double> & k1s, vector<double> & k2s, vector<double> & es, vector<vector<int> > & grid);
  //! Statistics on coarsegrained grid.
  /**
  * Coarse graines the grid and performs a series of statistics at different
  * coarse graining window sizes.
  * @param[out] ws       Window sizes.
  * @param[out] ss       Dimension.
  * @param[out] k1s      Size of PNG compressed string.
  * @param[out] k2s      Size of RLE compressed string.
  * @param[out] es       Entropy.
  * @param[in]  grid     Grid of the system.
  * @return              Nothing
  */
  double compress(vector<int> & vectorS);
  double compressPNG(vector<int> & vectorS, unsigned int window);
  //! Perform PNG compression on a std vector representing a square matrix.
  /**
  * Uses lodepng to perform a PNG compression to a std vector which
  * represents a square matrix.
  * @param[in] vectorS  Vector to compress
  * @param[in] width    Dide of the square matrix
  * @return             Nothing
  */
  int    boxCount(vector<int> & vectorS);
  //! Calculate the box-counting dimension.
  /**
  * Calculate box counting dimension (Minkowski-Bouligand). As the input is
  * already coarse grained we just have to calculate the sum of entries > 0
  * @param[in] coarseGrained Coarse grained vector.
  * @returns   int           Box counting dimension
  */
 private:
  int x;
  int y;
};
#endif
