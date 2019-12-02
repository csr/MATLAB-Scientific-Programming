/*
   Purpose: Area approximation using Monte Carlo method
   Author: Cesare De Cal
   Date: December 6, 2019
   Compiling: execute the .sh file from the command line. The compile file may need adjustments depending
   on the machine you're using.
   Compiling options depend on your machine and settings:
   https://software.intel.com/en-us/articles/intel-mkl-link-line-advisor
*/

#include "omp.h"
#include "mkl_vsl.h"
#include <stdio.h>
#include <math.h>

#define N 163840
#define LOOPS 1000

long idum = -87654321;

int main() {
  // Create and initialize a stream/streams
  //int threadID;
  int numberOfThreads = omp_get_max_threads();

  VSLStreamStatePtr stream[numberOfThreads];

  for (int i = 0; i < numberOfThreads; i++) {
    int errorCode = 0;

    errorCode = vslNewStream(&stream[i], VSL_BRNG_MCG59, idum);
    if (errorCode) {
      printf("vslNewStream failed\n");
      return 1;
    }
    errorCode = vslLeapfrogStream(stream[i], i, numberOfThreads);
    if (errorCode) {
      printf("vslLeapfrogStream failed\n");
      return 1;
    }
  }

  printf("Successfully initialized the threads");

  // Call one or more RNGs

  // Process the output

  // Delete the stream/streams

  return 0;
}