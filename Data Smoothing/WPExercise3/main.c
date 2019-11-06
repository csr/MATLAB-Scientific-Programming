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
  printf("$$\n\\begin{bmatrix}\n");
  for (int i = 0; i < vector->size; i++) {
    printf("%.15e\\\\\n", gsl_vector_get(vector, i));
  }
  printf("\\end{bmatrix}\n$$\n");
  printf("\n");
}

void printMatrixContents(gsl_matrix *matrix) {
  printf("$$\n\\begin{bmatrix}\n");
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
  printf("\\end{bmatrix}\n$$\n");
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

  // Fill coefficients matrix A by using basis functions
  for (int i = 0; i < matrixA->size1; i++) {
    for (int j = 0; j < matrixA->size2; j++) {
      gsl_matrix_set(matrixA, i, j, calculateBasisFunction(j, x[i]));
    }
  }
  printf("This is matrix A:\n");
  printMatrixContents(matrixA);

  // Calculate the condition number
  // There is no function in GSL to directly compute this number
  // the condition number is given by taking the absolute value of the ratio of the largest singular value and the smallest singular value
  // cond(A) = abs( largest_sing_val / smallest_sing_val )
  gsl_matrix *matrixV = gsl_matrix_alloc(matrixA->size2, matrixA->size2);
  gsl_vector *vectorS = gsl_vector_alloc(matrixA->size2);
  gsl_vector *vectorWorkspace = gsl_vector_alloc(matrixA->size2);
  gsl_linalg_SV_decomp(matrixA, matrixV, vectorS, vectorWorkspace);

  printf("Singular diagonal vector:\n");
  printVectorContents(vectorS);

  double minSingularValue, maxSingularValue;
  gsl_vector_minmax(vectorS, &minSingularValue, &maxSingularValue);
  printf("Max: %.9e, min: %.9e\n", maxSingularValue, minSingularValue);

  double conditionNumber = fabs(maxSingularValue/minSingularValue);
  printf("The condition number of the coefficients matrix is %.15e\n", conditionNumber);

  // Prepare column vector
  gsl_vector *vectorB = gsl_vector_alloc(matrixA->size1);
  for (int i = 0; i < matrixA->size1; i++) {
    gsl_vector_set(vectorB, i, y[i]);
  }
  printf("This is column vector b:\n");
  printVectorContents(vectorB);

  // Solving the linear system with QR decomposition
  // Note: QR matrix must be square
  gsl_matrix *matrixQR = gsl_matrix_alloc(matrixA->size1, matrixA->size2);
  gsl_matrix_memcpy(matrixQR, matrixA);

  // Note: size of tau must be MIN(M,N)
  int minBetweenRowsAndColumns = matrixA->size1;
  if (minBetweenRowsAndColumns > matrixA->size2) {
    minBetweenRowsAndColumns = matrixA->size2;
  }

  // Solve system
  gsl_vector *vectorTau = gsl_vector_alloc(minBetweenRowsAndColumns);
  gsl_vector *vectorX = gsl_vector_alloc(matrixA->size2);
  gsl_vector *vectorResidual = gsl_vector_alloc(matrixA->size1);

  gsl_vector_set_zero(vectorTau);
  gsl_linalg_QR_decomp(matrixQR, vectorTau);

  printf("QR decomposition:\n");
  printMatrixContents(matrixQR);

  gsl_linalg_QR_lssolve(matrixQR, vectorTau, vectorB, vectorX, vectorResidual);

  printf("Solutions vector:\n");
  printVectorContents(vectorX);

  printf("Residual vector:\n");
  printVectorContents(vectorResidual);

  // Calculate residual vector Euclidian norm
  

  // Free memory
  gsl_matrix_free(matrixA);
  gsl_vector_free(vectorB);
  gsl_vector_free(vectorTau);

  return 0;
}