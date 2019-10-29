//============================================================================
// Name        : main.c
// Author      : Cesare De Cal
// Version     :
// Copyright   : Cesare De Cal
// Description : Exercise 7 - System of Linear Equations
//============================================================================

#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

// Useful: https://gist.github.com/bjd2385/7f4685e703f7437e513608f41c65bbd7 (LU decomposition)
// Useful: https://github.com/rwinlib/gsl/blob/master/include/gsl/gsl_linalg.h#L173 (GEPP)

gsl_matrix *createMatrix(int size) {
  gsl_matrix *matrix = gsl_matrix_alloc(size, size);
  gsl_matrix_set_zero(matrix);

  for (int i = 1; i <= size; i++) {
    for (int j = 1; j <= size; j++) {
      // Fill diagonal
      if (i == j) {
        if ((i+1) % 3 == 0) {
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
    printf("%.10f\n", gsl_vector_get(vector, i));
  }
  printf("\n");
}

void printMatrixContents(gsl_matrix *matrix) {
  for (int i = 0; i < matrix->size1; ++i) {
    for (int j = 0; j < matrix->size2; ++j) {
      printf("%.10f ", gsl_matrix_get(matrix, i, j));
    }
    printf("\n");
  }
  printf("\n");
}

int main() {
  int size = 5;

  printf("Creating matrix A:\n");
  gsl_matrix *matrix = createMatrix(size);
  printMatrixContents(matrix);

  printf("Creating vector y (b):\n");
  gsl_vector *bVector = yVector(matrix->size2);
  printVectorContents(bVector);

  // Solve system using LU decomposition
  gsl_matrix *luMatrix = gsl_matrix_alloc(matrix->size1, matrix->size2);
  gsl_permutation *permutation = gsl_permutation_alloc(matrix->size1);
  int signum; // Sign of the permutation
  // Copy A over newly created matrix
  gsl_matrix_memcpy(luMatrix, matrix);
  // Compute LU decomposition
  gsl_linalg_LU_decomp(luMatrix, permutation, &signum);
  printf("LU decomposition of A:\n");
  printMatrixContents(luMatrix);

  // Result vector v
  gsl_vector *xVector = gsl_vector_alloc(matrix->size2);
  gsl_vector_set_zero(xVector);

  gsl_linalg_LU_solve(luMatrix, permutation, bVector, xVector);

  printf("Solutions x vector:\n");
  printVectorContents(xVector);

  // Calculate condition number
  // There is no function in GSL to directly compute this number
  // the condition number is given by taking the absolute value of the ratio of the largest singular value and the smallest singular value
  // cond(A) = abs( largest_sing_val / smallest_sing_val )
  // ...
  // compute condition number
  // ...


  return 0;
}

