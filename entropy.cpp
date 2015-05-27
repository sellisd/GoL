#include <iostream>
#include <cstdlib>
#include <cmath>
#include <map>
#include <vector>
#include "entropy.h"

using namespace std;

entropy::entropy(void){
  exit(1);
}

entropy::entropy(int a, int b){
  x = a;
  y = b;
}
double entropy::log2( double x ) {
   return log( x ) / log( 2 ) ;
}


void entropy::hist(map<int,double> & hist, vector<int> & vectorS){
 for(vector<int>::iterator it = vectorS.begin(); it != vectorS.end(); ++it){
   if(hist.find((*it)) != hist.end()){   //if element is already in map increment
     hist[(*it)]++;
   }else{    //else insert
     hist.insert(pair<int,double> ((*it),1.)); //count how many times observed
   }
 }
 //divide by total to get frequencies
 for(map<int,double>::iterator it = hist.begin(); it != hist.end(); ++it){
   hist[(*it).first] = (*it).second/double(vectorS.size());
 }
}

double entropy::infEntropy(map<int, double> & hist){
  double H = 0;
  for(map<int,double>::iterator it = hist.begin(); it != hist.end(); ++it){
    double p = (*it).second;
    H += p*log2(p);
  }
  return -H;
}


void entropy::pattern(map<int,double> & p, vector<vector<int> > & grid){
  for(int window = 2; window < x; window*=2){
    vector<int> cg;
    this->coarseGrain(cg, window, grid);
    map<int,double> histogram;
    this->hist(histogram, cg);
    pair<int,double> we(window,this->infEntropy(histogram));
    p.insert(we);
  }
}

void entropy::coarseGrain(vector<int> & coarseGrained, int window, vector<vector<int> > & grid){
  //non overlapping windows without error check, x and y should be powers of 2
  for(int I = 0; I < x; I+=window){
    for(int J = 0; J < y; J+=window){
      int sum = 0;
      int counter = 0;
      for(int i = 0; i < window; i++){
      	for(int j = 0; j< window; j++){
          sum+=grid.at(i+I).at(j+J);
          counter++;
	       }
      }
      //  double mean = sum/double(counter);
      coarseGrained.push_back(sum);
    }
  }
}
