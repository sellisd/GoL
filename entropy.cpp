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

void entropy::pattern(vector<int> & ws, vector<int> & ss, vector<double> & k1s, vector<double> & k2s, vector<double> & es, vector<vector<int> > & grid){
  //for Dimension use larger range of window values
  for(int window = 1; window <= x; window*=2){
    //  for(int window = 2; window < x; window*=2){
    ws.push_back(window);
    vector<int> cg;
    this->coarseGrain(cg, window, grid);
    // calculate Dimension
    int S = this->boxCount(cg);
    ss.push_back(S);
    // calculate Complexity
    double K1 = compressPNG(cg, x/window);
    k1s.push_back(K1);
    double K2 = compress(cg);
    k2s.push_back(K2);
    // calculate Entropy
    map<int,double> histogram;
    this->hist(histogram, cg);
    double H = this->infEntropy(histogram);
    es.push_back(H);
  }
}

void extractSubGrid(vector<vector<int> > & grid, vector<int> subgrid, int width, int x, int y){
  for( int I = x; I < x + width; I++){
    for(int J = y; J < y + width; J++){
      subgrid.push_back(grid.at(I).at(J));
    }
  }
}

pair<double, double> entropy::cornerComplexity(vector<vector<int> > & grid, int cornerWidth = 8){
  //Calculate complexity of top left square corner with width w
  //calculate K1 for the top left corner of width = 8
  vector<int> cornerTopLeft;
  vector<int> cornerBottomRight;
  for(int I = 0; I < cornerWidth; I++){
    for(int J = 0; J < cornerWidth; J++){
      cornerTopLeft.push_back(grid.at(I).at(J));
    }
  }
/*
  for(int I = x - cornerWidth; I < x; I++){
    for(int J = y - cornerWidth; J < y; J++){
      cornerBottomRight.push_back(grid.at(I).at(J));
    }
  }
  */
  for( int I = (x-cornerWidth)/2; I <(x-cornerWidth)/2+cornerWidth; I++){
    for(int J = (y-cornerWidth)/2; J <(y-cornerWidth)/2+cornerWidth; J++){
      cornerBottomRight.push_back(grid.at(I).at(J));
    }
  }

  double cornerTopLeftComplexity = compressPNG(cornerTopLeft, cornerWidth);
  double cornerBottomRightComplexity = compressPNG(cornerBottomRight, cornerWidth);
  pair<int, int> cornerComplexity;
  cornerComplexity.first = cornerTopLeftComplexity;
  cornerComplexity.second = cornerBottomRightComplexity;
  return(cornerComplexity);
}

void entropy::coarseGrain(vector<int> & coarseGrained, int window, vector<vector<int> > & grid){
  // non overlapping windows without error check, x and y should be powers of 2
  // window is the window size
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
  //and return compressed size
  return double(compressed.size()); //return size of compressed vector
}

double entropy::compressPNG(vector<int> & vectorS, unsigned int width){
  /*
    use lodepng
    */
//    make sure that max value is no more than 254 to be a valid color
  vector<int>::iterator M = max_element(vectorS.begin(),vectorS.end());
  if(M == vectorS.end()){
    cerr<<"Error: empty array"<<endl;
    exit(1);
  }
  if(*M > 255*255-1){
    cerr<<"Error: cannot code int>65024 using only the Red and Green chanel"<<endl;
    exit(1);
  }
  vector<unsigned char> uncompressed;
  uncompressed.resize(width * width * 4);
  int counter = 0;
  for(unsigned i = 0; i < width; i++){
    for(unsigned j = 0; j < width; j++){
      int value = vectorS.at(counter)+1;
      int div = ceil(double(value)/255.);
      uncompressed[4 * width * i + 4 * j + 0] = div; // R
      uncompressed[4 * width * i + 4 * j + 1] = value-255*(div-1); // G
      uncompressed[4 * width * i + 4 * j + 2] = 1; // B
      uncompressed[4 * width * i + 4 * j + 3] = 255; // alpha
      counter++;
    }
  }
  vector<unsigned char> compressed;
  //lodepng::State state;
  //LodePNGFilterStrategy filter = LFS_ZERO;
  //state.encoder.filter_strategy = filter;
  //unsigned error = lodepng::encode(compressed,uncompressed, width, width, state);
  unsigned error = lodepng::encode(compressed,uncompressed, width, width);
  double compSize = -1;
  if(!error){
    compSize = double(compressed.size());
    /* save image
       const char* filename2 = "test2.png";
       lodepng::save_file(compressed,filename2);
    */
  }else{
    cerr<<"Ups"<<endl;
    exit(1);
  }
  return compSize;
}

int entropy::boxCount(vector<int> & coarseGrained){
  //calculate box counting dimension (Minkowski-Bouligand)
  //the input is already coarse grained so we just have to calculate the sum of entries > 0
  int sum = 0;
  for(vector<int>::iterator it = coarseGrained.begin(); it != coarseGrained.end();  ++it){
    if ((*it)>0){
      sum++;
    }
  }
  return sum;
}
