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
#include <mkl_vsl.h>
#include <stdio.h>
#include <math.h>

#define N 163840
#define LOOPS 1000

// Seed
long idum = -87654321;

int main() {
  // Create and initialize a stream/streams
  int threadID;

  // The maximum number of threads that can execute concurrently in a single parallel region.
  int numberOfThreads = omp_get_max_threads();

  printf("Max number of parallel threads is %d\n", numberOfThreads);

  VSLStreamStatePtr stream[numberOfThreads];

  for (int i = 0; i < numberOfThreads; i++) {
    int errorCode = 0;

    // Creates and initializes a random stream
    errorCode = vslNewStream(&stream[i], VSL_BRNG_MCG59, idum);
    if (errorCode) {
      printf("vslNewStream failed\n");
      return 1;
    }

    // Initializes a stream using the leapfrog method.
    errorCode = vslLeapfrogStream(stream[i], i, numberOfThreads);
    if (errorCode) {
      printf("vslLeapfrogStream failed\n");
      return 1;
    }
  }

  printf("Successfully initialized the threads\n");

  /// loop over the number of threads
  long randomNumbersPerThread = 1 * N;

  // global total variables; parallel loops will add to it
  long insideArea = 0;

  #pragma omp parallel private(threadID) reduction( + : insideArea)
  {
    threadID = omp_get_thread_num();
    double randomNumbers[randomNumbersPerThread];

    // generate the random samples in [1, 3]
    vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream[threadID], randomNumbersPerThread, randomNumbers, 1, 3);

      for (int i = 0; i < N; ++i) {
        printf("Hola");
        /// check for points in cone or sphere respectively
      }

      /// add to totals
  }
  
  printf("Total area is %lf", insideArea);
  /// clean up
  for ( int i = 0; i < numberOfThreads; i++ ) {
    vslDeleteStream(&stream[i]);
  }

  return 0;
}