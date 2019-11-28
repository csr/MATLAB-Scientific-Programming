/*
   Purpose: Area approximation using Monte Carlo method
   Author: Cesare De Cal
   Date:

   Compiling:
    source /opt/intel/compilers_and_libraries_2019.5.281/mac/mkl/bin/mklvars.sh intel64
    gcc -fopenmp -m64 -I${MKLROOT}/include -c template.c
    gcc -L${MKLROOT}/lib/intel64 -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_gnu_thread -lmkl_core -lgomp -lpthread -lm -ldl template.o -o template
    time OMP_NUM_THREADS=5 ./template
*/

#include "omp.h"
#include "mkl_vsl.h"
#include <stdio.h>
#include <math.h>

#define N 163840
#define LOOPS 1000

long idum = -87654321;

int main(void) {
  // Initialize the threads
  int threadID;
  int numberOfThreads = omp_get_max_threads();

  VSLStreamStatePtr stream[numberOfThreads];

  for (int i = 0; i < numberOfThreads; i++) {
    int errorCode = 0;

    errorCode = vslNewStream(&stream[i], VSL_BRNG_MCG59, idum);
    if (errorCode) {
      printf( "vslNewStream failed\n");
      return 1;
    }
    errorCode = vslLeapfrogStream(stream[i], i, numberOfThreads);
    if (errorCode) {
      printf("vslLeapfrogStream failed\n");
      return 1;
    }
  }

  // Loop over the number of threads
  long randomNumbersPerThread = 3 * N;

  // global total variables; parallel loops will add to it
  // k_ == in volume; n_ == possibly in volume
  long tk_cone = 0, tn_cone = 0;
  long tk_sphere = 0, tn_sphere = 0;

  #pragma omp parallel private( threadID ) reduction( + : tk_cone, tn_cone, tk_sphere, tn_sphere )
  {
    threadID = omp_get_thread_num();

    int n = 0;

    double randomNumbers[randomNumbersPerThread];

    for (int j = 0; j < LOOPS; ++j) {

      // generate the random samples in [-1,1]
      vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream[threadID], randomNumbersPerThread, randomNumbers, -1, 1);

      for (int i = 0; i < N; ++i) {
        int x = randomNumbers[n++];
        int y = randomNumbers[n++];
        int z = randomNumbers[n++] + 1;

        /// check for points in cone or sphere respectively
      }

      /// add to totals
      // tk_cone += ...
      // tn_cone +=  ...
      // tk_sphere += ...
      // tn_sphere += ...
    }

  } // end of thread

  /// average of results

  /// clean up
  for (int i = 0; i < numberOfThreads; i++) {
    vslDeleteStream(&stream[i]);
  }
}