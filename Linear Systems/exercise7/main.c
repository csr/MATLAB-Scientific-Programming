//============================================================================
// Name        : main.c
// Author      : Cesare De Cal
// Version     :
// Copyright   : Cesare De Cal
// Description : Exercise 7 - System of Linear Equations
//============================================================================

#include <stdio.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

// Useful: https://gist.github.com/bjd2385/7f4685e703f7437e513608f41c65bbd7 (LU decomposition)
// Useful: https://github.com/rwinlib/gsl/blob/master/include/gsl/gsl_linalg.h#L173 (GEPP)

// Just a small test to see if GSL works ok.
void test() {
  double x = 5.0;
  double y = gsl_sf_bessel_J0(x);
  printf("J0(%g) = % .18e\n", x, y);
}

gsl_matrix *createMatrix(int size) {
  gsl_matrix *matrix = gsl_matrix_alloc(size, size);
  gsl_matrix_set_zero(matrix);

  for (int i = 1; i <= size; i++) {
    for (int j = 1; j <= size; j++) {
      // Fill diagonal
      if (i == j) {
        if (i % 2 == 0) {
          double value = (2.0*(i+1))/3;
          gsl_matrix_set(matrix, i-1, j-1, value);
        } else {
          gsl_matrix_set(matrix, i-1, j-1, 1);
        }
        // Fill adjacent lower diagonal
      } else if (i == j+1) {
        gsl_matrix_set(matrix, i-1, j-1, 1);
        // Fill adjacent upper diagonal
      } else if (i+1 == j) {
        gsl_matrix_set(matrix, i-1, j-1, -1);
      }
    }
  }
  return matrix;
}

// Allocate right-hand side vector y
gsl_vector *yVector(int size) {
  gsl_vector *vector = gsl_vector_alloc(size);
  gsl_vector_set_zero(vector);

  // Fill element at index 0 with 1
  gsl_vector_set(vector, 0, 1);
  return vector;
}

// Helper methods

void printVectorContents(gsl_vector *vector) {
  for (int i = 0; i < vector->size; i++) {
    printf("v_%d = %g\n", i, gsl_vector_get(vector, i));
  }
  printf("\n");
}

void printMatrixContents(gsl_matrix *matrix) {
  for (int i = 0; i < matrix->size1; ++i) {
    for (int j = 0; j < matrix->size2; ++j) {
      printf("%f ", gsl_matrix_get(matrix, i, j));
    }
    printf("\n");
  }
  printf("\n");
}

int main() {
  int n = 10;

  printf("Creating matrix A:\n");
  gsl_matrix *matrix = createMatrix(n);
  printMatrixContents(matrix);

  printf("Creating vector y:\n");
  gsl_vector *vector = yVector(n);
  printVectorContents(vector);

  // Solve system using LU decomposition
  int signum;
  gsl_permutation *permutation = gsl_permutation_alloc(n);
  printf("LU decomposition of A:\n");
  gsl_linalg_LU_decomp(matrix, permutation, &signum);
  printMatrixContents(matrix);

  return 0;
}
