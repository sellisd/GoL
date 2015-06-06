#include <iostream>
#include <cstdlib>
#include <cmath>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include "lodepng.h"
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

void entropy::pattern(map<int,pair<double,double> > & p, vector<vector<int> > & grid){
  for(int window = 2; window < x/2; window*=2){
    vector<int> cg;
    this->coarseGrain(cg, window, grid);
    double K = compressPNG(cg, x/window);
    //double K = compress(cg);
    map<int,double> histogram;
    this->hist(histogram, cg);
    pair<double,double> entrCompl(this->infEntropy(histogram),K);
    pair<int,pair<double,double> > we(window,entrCompl);
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
      coarseGrained.push_back(sum);
    }
  }
}

double entropy::compress(vector<int> & vectorS){
  // compress vector (encode as value/copy list, eg 000111002 -> 03130221)
  vector<int> compressed;
  int prev = vectorS.front();
  int counter = 0;
  for(vector<int>::iterator it = vectorS.begin(); it != vectorS.end(); ++it){
    if((*it) == prev){
      counter++;
    }else{
      compressed.push_back(prev);
      compressed.push_back(counter);
      prev = (*it);
      counter = 1;
    }
  }
  int last = vectorS.back();
  if(last == prev){
    compressed.push_back(last);
    compressed.push_back(counter);
  }else{
    compressed.push_back(last);
    compressed.push_back(1);
  }
  //and return compression ratio
  return double(compressed.size())/double(vectorS.size()); //return size of uncompressed vector
}

double entropy::compressPNG(vector<int> & vectorS, int width){
  /*
    use lodepng
    */
//    make sure that max value is no more than 254 to be a valid color
  vector<int>::iterator M = max_element(vectorS.begin(),vectorS.end());
  if(M == vectorS.end()){
    cerr<<"Error: empty array"<<endl;
    exit(1);
  }
  if(*M > 254){
    cerr<<"Error: cannot code char from int>255 using only the Red chanel"<<endl;
    exit(1);
  }
  vector<unsigned char> uncompressed;
  uncompressed.resize(width * width * 4);
  int counter = 0;
  for(unsigned i = 0; i < width; i++){
    for(unsigned j = 0; j < width; j++){
      uncompressed[4 * width * i + 4 * j + 0] = vectorS.at(counter)+1; // R
      uncompressed[4 * width * i + 4 * j + 1] = 1; // G
      uncompressed[4 * width * i + 4 * j + 2] = 1; // B
      uncompressed[4 * width * i + 4 * j + 3] = 255; // alpha
      counter++;
    }
  }
  vector<unsigned char> compressed;
  unsigned error = lodepng::encode(compressed,uncompressed, width, width);
  double ratio = -1;
  if(!error){
    ratio = double(compressed.size())/double(uncompressed.size());
    /* save image
       const char* filename2 = "test2.png";
       lodepng::save_file(compressed,filename2);
    */
  }else{
    cerr<<"Ups"<<endl;
    exit(1);
  }
  return ratio;
}
