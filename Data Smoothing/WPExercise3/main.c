#include <stdio.h>
#include <math.h>
#include "gsl/gsl_sf_gamma.h"
#include "gsl/gsl_sf_pow_int.h"
#include "gsl/gsl_linalg.h"

double calculateBinomialCoefficient(int n, int k) {
  // formula: (n k) = n! / (k!(n-k))
  double numerator = gsl_sf_fact(n);
  double denominator = gsl_sf_fact(k)*gsl_sf_fact(n-k);
  return numerator/denominator;
}
// φ_{3,i}(x) = (3 i)x^i (1-x)^(3-i)
double calculateBasisFunction(int i, double x) {
  double binomialCoefficient = calculateBinomialCoefficient(3, i); // (3 i)
  double secondTerm = gsl_sf_pow_int(x, i); // x^i
  double thirdTerm = gsl_sf_pow_int(1-x, 3-i); // (1-x)^(3-i)
  return binomialCoefficient*secondTerm*thirdTerm;
}

// sqrt ()
double calculateFunction(int j, double x[], double y[]) {
  double sum = 0;

  for (int i = 0; i < j; i++) {
    double basisFunctionOutput = 0;
    double difference = basisFunctionOutput - y[i];
    double differenceSquared = gsl_sf_pow_int(difference, 2);
    sum += differenceSquared;
  }

  return sqrt(sum);
}

// Helper methods
void printVectorContents(gsl_vector *vector) {
  for (int i = 0; i < vector->size; i++) {
    printf("%.15e\\\\\n", gsl_vector_get(vector, i));
  }
  printf("\n");
}

void printMatrixContents(gsl_matrix *matrix) {
  for (int i = 0; i < matrix->size1; ++i) {
    for (int j = 0; j < matrix->size2; ++j) {
      printf("%.15e ", gsl_matrix_get(matrix, i, j));

      if (j == matrix->size2-1) {
        printf("\\\\");
      } else {
        printf("& ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

int main() {
  double x[] = {0.0, 0.6, 1.5, 1.7, 1.9, 2.1, 2.3, 2.6, 2.8, 3.0, 3.6, 4.7, 5.2, 5.7, 5.8, 6.0, 6.4, 6.9, 7.6, 8.0};
  double y[] = {-0.80, -0.34, 0.59, 0.59, 0.23, 0.10, 0.28, 1.03, 1.50, 1.44, 0.74, -0.82, -1.27, -0.92, -0.92, -1.04, -0.79, -0.06, 1.00, 0.00};

  printf("j . x_j . y_j\n");
  for (int i = 0; i < sizeof(x)/sizeof(x[0]); i++) {
    // Print input table in LaTeX-friendly format
    printf("%d & %.1f & %.2f\\\\\n", i, x[i], y[i]);
  }

  // Prepare coefficients matrix A
  int rows = 20;
  int columns = 4;
  gsl_matrix *matrixA = gsl_matrix_alloc(rows, columns);

  // Iterate over rows
  for (int i = 0; i < matrixA->size1; i++) {
    // Iterate over columns
    for (int j = 0; j < matrixA->size2; j++) {
      gsl_matrix_set(matrixA, i, j, calculateBasisFunction(j, x[i]));
    }
  }
  printf("This is matrix A:\n");
  printMatrixContents(matrixA);

  // Prepare column vector
  gsl_vector *vectorB = gsl_vector_alloc(matrixA->size1);
  for (int i = 0; i < matrixA->size1; i++) {
    gsl_vector_set(vectorB, i, y[i]);
  }
  printf("This is column vector b:\n");
  printVectorContents(vectorB);

  // Basis functions
  for (int i = 0; i < 4; i++) {
    double functionOutput = calculateBasisFunction(i, 2);
    printf("Calculating basis function for i (%d): %lf\n", i, functionOutput);
  }

  double n = 40.0;
  double k = 3.0;
  printf("Binomial coefficient of %lf and %lf: %lf\n", n, k, calculateBinomialCoefficient(n, k));

  // Free memory
  gsl_matrix_free(matrixA);

  return 0;
}