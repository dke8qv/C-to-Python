#include "mylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// here we check if the flag EXTERNC is set, if it is then
// we will tell the compiler to treat the code below a C code
// generating the library

#ifdef EXTERNC
extern "C" {
#endif

// estimate pi from the dart throwing method
double findPi(long nthrows=100*1000*1000){
  srand48((long)time(NULL));
  long count=0;
  for (int i=0; i<nthrows; ++i){
    double x=drand48();
    double y=drand48();
    if (x*x+y*y < 1) ++count;
  }
  return 4.0*count/nthrows;
}
 

// return the magnitude of a complex number
double magnitude(double re, double im){
  return sqrt(re*re+im*im);
}

double HSVolume(int d, long long N, double r) {
  // Monte Carlo volume of a d-D hypersphere of radius r, using N pseudorandom points
  // Method: throw in hypercube [-r, r]^d; volume = (2r)^d * (hits/N)
  srand48((long)time(NULL));
  long long hits = 0;

  // quick path: d<=0 or N<=0
  if (d <= 0 || N <= 0 || r <= 0.0) return 0.0;

  for (long long n = 0; n < N; ++n) {
    // draw d coords in [-r, r]
    double rsq = 0.0;
    for (int k = 0; k < d; ++k) {
      // uniform in [0,1) then affine-map to [-r, r]
      double xk = (2.0*drand48() - 1.0) * r;
      rsq += xk * xk;
      // early exit if already outside
      if (rsq > r*r) { // outside
        // skip the remaining coords
        // advance loop index quickly
        for (++k; k < d; ++k) { (void)drand48(); } // consume RNG to keep calls consistent (optional)
        goto done_point;
      }
    }
    // inside if rsq <= r^2
    ++hits;
  done_point:
    ;
  }

  // hypercube volume = (2r)^d
  double vol_hypercube = 1.0;
  for (int k = 0; k < d; ++k) vol_hypercube *= (2.0 * r);
  return vol_hypercube * (double)hits / (double)N;
}



int mandel_test(double c_re, double c_im, int NTRIALS){  
  // If a point is in the set, its magnitude will remain bounded by
  // 2.0 over iterations of z -> z^2 + C.  Stop the loop after a 
  // maximum of NTRIALS and consider this point to be in the set

  double z_re = c_re;
  double z_im = c_im;
  int counts = 1;
  while (magnitude(z_re,z_im)<=2.0  && counts<NTRIALS) {
    counts++;
    double re=z_re;  // careful! keep old values for calculation
    double im=z_im;
    // z -> z^2
    z_re = re*re-im*im;
    z_im = 2*re*im;
    // add c to z^2
    z_re = z_re + c_re;
    z_im = z_im + c_im;
  }
  return counts;
}


// explore the Mandelbrot set
// we pass the image buffer as a 1D array, and access the pixels
// using pointer arithmatic
// eg for an array a[n][m], n=nrow, m=mcolumns
// a[0] = a[0][0]
// a[m] = a[1][0]
// a[m+1] = a[1][1]
// ...
void mandel(double *img, double re1, double re2, double im1, double im2,
	    int nr, int ni, int NTRIALS){
  double dx=(re2-re1)/nr;
  double dy=(im2-im1)/ni;
  // loop over grid starting in lower left corner
  for (int j=0; j<ni; ++j){
    double im=im1+j*dy;
    for (int i=0; i<nr; ++i){
      double re=re1+i*dx;
      img[j*ni+i]=mandel_test(re,im,NTRIALS);
    }
  }
}

  

#ifdef EXTERNC
}
#endif




/*
int main(){
  findPi();
  return 0;
} 
*/
