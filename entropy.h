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
  void   pattern(vector<int> ws, vector<int> ss, vector<double> k1s, vector<double> k2s, vector<double> es, vector<vector<int> > & grid);
  double compress(vector<int> & vectorS);
  double compressPNG(vector<int> & vectorS, unsigned int window);
  int    boxCount(vector<int> & vectorS);
 private:
  int x;
  int y;
};
#endif
