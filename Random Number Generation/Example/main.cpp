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

// Numbers per thread
#define N 163840

// Times the process is repeated
#define LOOPS 1000

// Seed
long idum = -87654321;

bool isInsideArea(double x, double y) {
  // x^3 + y^3 <= 29
  double firstCondition = pow(x, 3) + pow(y, 3);
  if (firstCondition > 29) {
    return false;
  }

  // y >= e^x - 2
  double secondCondition = pow(M_E, x) - 2;
  if (y < secondCondition) {
    return false;
  }

  return true;
}

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
  long areaSum = 0;
  
  // More info: http://pages.tacc.utexas.edu/~eijkhout/pcse/html/omp-data.html
  // #pragma omp parallel private(threadID) reduction(+ : insideArea) {
  //   threadID = omp_get_thread_num();

  //   // stuff here...
  // }
  
  /* Fork a team of threads giving them their own copies of variables */
  #pragma omp parallel private(numberOfThreads, threadID) reduction(+ : areaSum)
  {
    /* Obtain thread number */
    threadID = omp_get_thread_num();

    double randomNumbersX[randomNumbersPerThread];
    double randomNumbersY[randomNumbersPerThread];

    for (int j = 0; j < LOOPS; ++j) {
      // generate the random samples in [1, 3]
      vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream[threadID], randomNumbersPerThread, randomNumbersX, 1, 3);
      vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream[threadID], randomNumbersPerThread, randomNumbersY, -1, 4);
    
      for (int i = 0; i < N; ++i) {
        /// check for points in cone or sphere respectively
        double x = randomNumbersX[i++];
        double y = randomNumbersY[i++];
        bool isInside = isInsideArea(x, y);
        if (isInside == true) {
          // insideArea++;
          areaSum++;
        }
      }
    }

    printf("Hello World from thread = %d\n", threadID);
  }

  // double area = (double)num1/(double)num2;

  // printf("Total area is %\n", area);

  /// clean up
  for (int i = 0; i < numberOfThreads; i++) {
    vslDeleteStream(&stream[i]);
  }

  return 0;
}