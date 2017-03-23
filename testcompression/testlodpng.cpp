#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>    // std::min_element, std::max_element
#include <math.h>       /* ceil */
#include "lodepng.h"

//g++  -Wall -o run main.cpp entropy.cpp gol.cpp lg.cpp ca.cpp cani.cpp generateStatic.cpp randomv.cpp lodepng.cpp -lgsl -lgslcblas
//g++  -Wall -o run testlodpng.cpp lodepng.cpp

using namespace std;

double compressPNG(vector<int> & vectorS, unsigned int width){
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

int main(int argc, char* argv[]){
  std::vector<int> vectorS;
  int squareSide = 125;
  for(int i = 0; i < squareSide*squareSide; i++){
    vectorS.push_back(rand() % 100 + 1);
  }
  cout << compressPNG(vectorS, squareSide);
}
