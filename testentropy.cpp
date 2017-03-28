#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include "entropy.h"    // std::min_element, std::max_element


//g++  -Wall -o run testentropy.cpp entropy.cpp generateStatic.cpp randomv.cpp lodepng.cpp -lgsl -lgslcblas

using namespace std;

int main(int argc, char* argv[]){
  std::vector<int> vectorS;
  int squareSide = 64;
  for(int i = 0; i < squareSide*squareSide; i++){
    vectorS.push_back(rand() % 2);
  }
  map<int,double> h;
  entropy ef(64,64);

  ef.hist(h, vectorS);
  cout<<"Entropy of random string should be about 1";
  cout<<ef.infEntropy(h);
  /*for(map<int,double>::iterator it = h.begin(); it != h.end(); ++it){
     cout<<(*it).first<<' '<<(*it).second<<endl;
  }*/

}
