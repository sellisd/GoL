#include <time.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include "randomv.h"
using namespace std;
//! constructor
randomv::randomv(void){
  gsl_rng_env_setup();
  gsl_rng_default_seed = (unsigned long)time(0)*getpid();
  Gt = gsl_rng_default;
  Gr = gsl_rng_alloc (Gt);
}

//! constructor with seed
randomv::randomv(unsigned long seed){
  gsl_rng_env_setup();
  gsl_rng_default_seed = (unsigned long)time(0)*getpid();
  Gt = gsl_rng_default;
  Gr = gsl_rng_alloc (Gt);
}
//! Sample a random number from uniform distribution [0,1)
double randomv::sampleUniform(void){
  //[0,1)
  return gsl_rng_uniform(Gr);
}

int randomv::sampleUniformInt(int n){
 //~[0,n-1)
  return gsl_rng_uniform_int(Gr, n);
}

unsigned int randomv::sampleBinomial(double p, int N){
  return gsl_ran_binomial(Gr, p, N);
}

//! Sample a random number from a normal distribution
double randomv::sampleNormal(double sigma){
  return gsl_ran_gaussian(Gr, sigma);
}

double randomv::sampleNormal(double mu, double sigma){
  return gsl_ran_gaussian(Gr, sigma) + mu;
}

//! Sample a random number from an exponential distribution with mean mu
double randomv::sampleExponential(double mu){
  //mu: mean
  //mu = 1 / lambda
  return gsl_ran_exponential(Gr, mu);
}

double randomv::sampleGamma(double alpha, double beta){
  return gsl_ran_gamma(Gr, alpha, beta);
}

void randomv::sampleMultinomial(size_t K, unsigned int N, const double p[], unsigned int n[]){
  gsl_ran_multinomial(Gr, K, N, p, n);
}

double randomv::samplePareto(double alpha, double beta){
  return gsl_ran_pareto(Gr, alpha, beta);
}

double randomv::samplePoisson(double lambda){
  return gsl_ran_poisson(Gr, lambda);
}

void randomv::sampleDirVector(int dimensions, size_t n, double* x){
  gsl_ran_dir_nd(Gr, n, x); 
}


int randomv::sampleMyMultinomial(int NumOfGenotypes,unsigned int N, const double p[],unsigned int newGeneration[]){
  double cumulativeP[NumOfGenotypes];
  //initialize newGeneration[];
  for(int i = 0; i <NumOfGenotypes; i++){
    newGeneration[i] = 0;
  }
  double sum = 0;
  int returnValue = 0;
  for(int i = 0; i<NumOfGenotypes;i++){
    if(p[i]<0){
      returnValue = 2;
    }
    sum += p[i];
    cumulativeP[i]=sum;
  }
  if(sum == 0){
    returnValue = 3;
  }
  if(sum!=1){ //speed up by checking limits
  //if sum is not exactly one rescale probabilities
    for(int i = 0; i<NumOfGenotypes;i++){
      cumulativeP[i] = cumulativeP[i]/sum;
    }
    returnValue = sum;
  }
  vector<double> rs;
  for(unsigned int i = 0; i<N;i++){
    double r = (double)rand()/RAND_MAX;//distribution(generator);
    rs.push_back(r);
  }
  sort(rs.begin(),rs.end());
  //loop over array[N]
  int counter = 0;
  for(vector<double>::iterator it = rs.begin();
      it !=rs.end(); ++it){
    if ((*it)>cumulativeP[counter]){
      counter++;
    }
    if((*it)<cumulativeP[counter] && (counter==0?(*it)>0:(*it)>cumulativeP[counter-1]) ){
      newGeneration[counter]++;    
    }
  }
  return returnValue;
}
