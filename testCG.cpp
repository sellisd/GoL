#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include "entropy.h"    // std::min_element, std::max_element


//g++  -Wall -o run testCG.cpp entropy.cpp generateStatic.cpp randomv.cpp lodepng.cpp -lgsl -lgslcblas

using namespace std;

int main(int argc, char* argv[]){
  std::vector<int> vectorS;
  int side = 64;
  vector<int> cg;
  vector<vector<int> > grid;
  for(int i = 0; i < side; i++){
    vector<int> row;
    for( int j = 0; j <side; j++){
      row.push_back(rand()%2);
    }
    grid.push_back(row);
  }
  entropy ef(64,64);
  ef.coarseGrain(cg, 1, grid);
  for(int i = 0; i < side; i++){
    for( int j = 0; j <side; j++){
      cout<<grid.at(i).at(j)<<' ';
    }
    cout<<"\n";
  }
  for(vector<int>::iterator it = cg.begin(); it != cg.end(); ++it){
    cout<<(*it)<<'.';
  }
}
