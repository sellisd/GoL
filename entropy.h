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
  void   pattern(map<int,double> & p, vector<vector<int> > & grid);
  void   compress(void);
 private:
  int x;
  int y;
};
#endif
