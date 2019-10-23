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

// Useful: https://gist.github.com/bjd2385/7f4685e703f7437e513608f41c65bbd7 (LU decomposition)

// Just a small test to see if GSL works ok.
void test() {
  double x = 5.0;
  double y = gsl_sf_bessel_J0(x);
  printf("J0(%g) = % .18e\n", x, y);
}

gsl_matrix *createMatrix(int size) {
  gsl_matrix *matrix = gsl_matrix_alloc(size, size);

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
      }
    }
  }


  return matrix;
}

// Allocate right-hand side vector y
gsl_vector *yVector(int size) {
  gsl_vector *vector = gsl_vector_alloc(size);

  // Fill element at index 0 with 1
  gsl_vector_set(vector, 0, 1);
  return vector;
}

// Helper methods

void printVectorContents(gsl_vector *vector, int size) {
  for (int i = 0; i < size; i++) {
    printf("v_%d = %g\n", i, gsl_vector_get(vector, i));
  }
}

void printSquareMatrixContents(gsl_matrix *matrix, int size) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      printf("%f ", gsl_matrix_get(matrix, i, j));
    }
    printf("\n");
  }
}

int main() {
  int n = 10;

  // Create matrix
  gsl_matrix *matrix = createMatrix(n);
  printSquareMatrixContents(matrix, n);

  // Allocate right-hand side vector y
  gsl_vector *vector = yVector(n);
  printVectorContents(vector, n);

  return 0;
}

