#ifndef ENTROPY_H
#define ENTROPY_H

using namespace std;
/**
 * Entropy calculations
 */
class entropy{
 public:
  entropy(void); //! Default constructor
  entropy(int x, int y); //! Constructor with size of grid
  double log2(double x); //! Base 2 logarithm
  void   hist(map<int,double> &, vector<int> & vectorS);
  //! Calculate histogram of symbols.
  /**
  * Calculates the frequency of symbols in a vector of integers.
  * @param[out] hist     Map of integer to double
  * @param[in]  vectorS  Symbol vector
  * @return              Nothing
  */
  double infEntropy(map<int,double> & hist);
  //! Calculate information entropy.
  /**
  * Calculates the information entropy from a map of symbol frequencies.
  * @param[in]  hist     Map of integer to double
  * @return              Information entropy in bits (log2)
  */
  void   coarseGrain(vector<int> & coarseGrained, int window, vector<vector<int> > & grid);
  //! Coarse grain grid by summation.
  /**
  * Non overlapping windows of side window are used to cover the whole grid and
  * within each window the sum of all cell values is calculated. There is no
  * checks for errors, so x and y should always be powers of 2.
  * @param[out] coarseGrained   One dimensional vector of coarse grained grid.
  * @param[in]  window          Side of window for coarse graining.
  * @param[in]  grid            Grid of system.
  * @return                     Nothing.
  */
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
  void statistics(vector<int> & subGrid, int subGridSide, vector<double> &results);
  //! Calculate statistics on a subgrid vector.
  /**
  * Calculates the Kolmogorov complexity, the information entropy and the density
  * of non-zero cells on a subgrid vector.
  * @param[in]  subGrid      Vector of subgrid.
  * @param[in]  subGridSide  Size of the square subgrid side.
  * @param[out] results      Vector with results [K, H, D]
  * @return                  Nothing.
  */
  void subGridStats(vector<vector<int> > &grid, vector<double> & topleftStats, vector<double> & centerStats, vector<double> & bottomrightStats);
  //! Statistics of three subgrids.
  /**
  * Calculate statistics at three square subgrids with side 8, the top left
  * corner, the center and the bottom right.
  * @param[in]  grid             Grid of the system.
  * @param[out] topleftStats     Statistics for top left subgrid
  * @param[out] centerStats      Statistics for center subgrid
  * @param[out] bottomrightStats Statistics for bottom right subgrid
  * @return              Nothing
  */
  void coarseGrainedStats(vector<vector<int> > &grid, map<int, vector<double> > & cgStats);
  //! Statistics on coarse grained grid.
  /**
  * Coarse grain the system's grid at different scales with non-overlapping
  * windows of size w = 1^i, with i \in (1, 2, 3, 4, 5, 6) and for each window
  * size calculate statistics.
  * @param[in]  grid             Grid of the system.
  * @param[out] cgStats          Statistics for each coarse graining window size.
  * @return              Nothing
  */
  double density(vector<int> & subgrid);
  //! Calculate the density of a subgrid.
  /**
  * Calculates the ratio of occupied cells to total cells.
  * @param[in]  subgrid  The subgrid vector.
  * @return              The density of the region
  */
  double compress(vector<int> & vectorS);
  //! Perform run length encoding compression.
  /**
  * Compress vector with a run length encoding list, e.g.: 000111002 -> 03130221.
  * @param[in] vectorS  Vector to compress
  * @return             Size of compressed vector.
  */
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
