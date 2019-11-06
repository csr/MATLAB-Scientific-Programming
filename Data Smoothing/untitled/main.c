//
//  main.c
//  Data smoothing
//
//  Created by Alessandro on 05/11/2018.
//  Copyright © 2018 Alessandro. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>
#define max 3
#define rows 20
#define columns 4

void fill_original_data(double matrix[rows][2]);
void fill(gsl_matrix *A, gsl_vector *b, double matrix[rows][2]);
double phi(int i, double value);
double binomial(int n, int k);
void fill_codomain(gsl_vector *y, gsl_vector *x, double matrix[rows][2]);
double complete_phi(double pos, gsl_vector *x);

void fill_monomial(gsl_matrix *A, gsl_vector *b, double matrix[rows][2]);
void fill_codomain_monomial(gsl_vector *y, gsl_vector *x, double matrix[rows][2]);
double sum_mu(double x, gsl_vector *coef);

void printVectorContents(gsl_vector *vector) {
  for (int i = 0; i < vector->size; i++) {
    printf("%.9e\\\\\n", gsl_vector_get(vector, i));
  }
  printf("\n");
}

void printMatrixContents(gsl_matrix *matrix) {
  for (int i = 0; i < matrix->size1; ++i) {
    for (int j = 0; j < matrix->size2; ++j) {
      printf("%.9e ", gsl_matrix_get(matrix, i, j));

      if (j == matrix->size2 - 1) {
        printf("\\\\");
      } else {
        printf("& ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

int main(int argc, const char * argv[]) {
  double matrix[rows][2]; // Original data
  gsl_vector *box = gsl_vector_calloc(rows); // To maintain the computed Ys

  printf("### Prima parte ###\n\n");

  gsl_matrix *A = gsl_matrix_calloc(rows, columns);
  gsl_vector *b1 = gsl_vector_calloc(rows);
  gsl_vector *r1 = gsl_vector_calloc(rows);
  int size_tau = 0;

  fill_original_data(matrix);
  fill(A, b1, matrix);
  printf("Matrix A:\n");
  printMatrixContents(A);

//	gsl_matrix_fprintf(stdout, A, "%.16e");

  size_tau = rows < columns ? rows : columns;
  gsl_vector *tau = gsl_vector_calloc(size_tau);
  gsl_linalg_QR_decomp(A, tau);

//	printf("OKOK\n");
//	gsl_matrix_fprintf(stdout, A, "%.16e");
//	printf("OKOK\n");
//	gsl_vector_fprintf(stdout, tau, "%.16e");

  gsl_vector *x = gsl_vector_alloc(columns);
  gsl_vector *residual = gsl_vector_alloc(rows);
  gsl_linalg_QR_lssolve(A, tau, b1, x, residual);
  // This residual I can use to compute the quadratic

  printf("\u03BB: \n");
  gsl_vector_fprintf(stdout, x, "%.16e");	// Computed x values

  fill(A, b1, matrix);

  printf("This is vector b:\n");
  printVectorContents(b1);

  // Using the computed lambdas, I calculate f(x) and put it in b.
  fill_codomain(b1, x, matrix);

  for(int i = 0; i < r1->size; i++) {
    gsl_vector_set(r1, i, matrix[i][1]-gsl_vector_get(b1, i));
  }
  printf("\nResidual: \n");
  gsl_vector_fprintf(stdout, r1, "%.16e");

  // double gsl_blas_dnrm2 (const gsl_vector * x)
  // Eucledian norm
  double square_root = gsl_blas_dnrm2(residual);
  printf("\nNorm of residual vector: %.16e\n", square_root);

  gsl_matrix *X = gsl_matrix_calloc(columns, columns);
  gsl_matrix *V = gsl_matrix_calloc(columns, columns);
  gsl_vector *S = gsl_vector_calloc(columns);
  gsl_vector *work = gsl_vector_calloc(columns);
  fill(A, box, matrix);

  gsl_linalg_SV_decomp_mod(A, X, V, S, work);
  double condition_number = gsl_vector_max(S) / gsl_vector_min(S);
  printf("\nCondition number of A matrix: %.16e\n", condition_number);

  // PRIMA DEVO COMPUTE IL RESIDUAL COME b - Ax
  // POI FILL MONOMIAL E SECONDA PARTE ESERCIZIO

  printf("\n\n\n### Seconda parte ###\n\n");
  gsl_vector *b2= gsl_vector_calloc(rows);
  gsl_vector *r2 = gsl_vector_calloc(rows);

  fill_monomial(A, b2, matrix);

  gsl_vector_set_zero(tau);
  gsl_linalg_QR_decomp(A, tau);

  gsl_vector_set_zero(x);
  gsl_vector_set_zero(residual);
  gsl_linalg_QR_lssolve(A, tau, b2, x, residual);

  printf("\u03BB: \n");
  gsl_vector_fprintf(stdout, x, "%.16e");	// Computed x values

  fill_monomial(A, b2, matrix);

  // Using the computed lambdas, I calculate f(x) and put it in b.
  fill_codomain_monomial(b2, x, matrix);

  for(int i = 0; i < r2->size; i++) {
    gsl_vector_set(r2, i, matrix[i][1]-gsl_vector_get(b2, i));
  }
  printf("\nResidual: \n");
  gsl_vector_fprintf(stdout, r2, "%.16e");

  // double gsl_blas_dnrm2 (const gsl_vector * x)
  // Eucledian norm
  square_root = gsl_blas_dnrm2(residual);
  printf("\nNorm of residual vector: %.16e\n", square_root);

  gsl_matrix_set_zero(X);
  gsl_matrix_set_zero(V);
  gsl_vector_set_zero(S);
  gsl_vector_set_zero(work);

  fill_monomial(A, box, matrix);

  gsl_linalg_SV_decomp_mod(A, X, V, S, work);
  condition_number = gsl_vector_max(S) / gsl_vector_min(S);
  printf("\nCondition number of A matrix: %.16e\n", condition_number);

  printf("\n\n\nDifferences between the two computed y values:\n");
  gsl_vector_sub(b2, b1);
  gsl_vector_fprintf(stdout, b2, "%.16e");

  return 0;
}

void fill_original_data(double matrix[rows][2]) {
  int k = 0;
  matrix[k][0] = 0.0;
  matrix[k][1] = -0.80;
  k++;
  matrix[k][0] = 0.6;
  matrix[k][1] = -0.34;
  k++;
  matrix[k][0] = 1.5;
  matrix[k][1] = 0.59;
  k++;
  matrix[k][0] = 1.7;
  matrix[k][1] = 0.59;
  k++;
  matrix[k][0] = 1.9;
  matrix[k][1] = 0.23;
  k++;
  matrix[k][0] = 2.1;
  matrix[k][1] = 0.10;
  k++;
  matrix[k][0] = 2.3;
  matrix[k][1] = 0.28;
  k++;
  matrix[k][0] = 2.6;
  matrix[k][1] = 1.03;
  k++;
  matrix[k][0] = 2.8;
  matrix[k][1] = 1.50;
  k++;
  matrix[k][0] = 3.0;
  matrix[k][1] = 1.44;
  k++;
  matrix[k][0] = 3.6;
  matrix[k][1] = 0.74;
  k++;
  matrix[k][0] = 4.7;
  matrix[k][1] = -0.82;
  k++;
  matrix[k][0] = 5.2;
  matrix[k][1] = -1.27;
  k++;
  matrix[k][0] = 5.7;
  matrix[k][1] = -0.92;
  k++;
  matrix[k][0] = 5.8;
  matrix[k][1] = -0.92;
  k++;
  matrix[k][0] = 6.0;
  matrix[k][1] = -1.04;
  k++;
  matrix[k][0] = 6.4;
  matrix[k][1] = -0.79;
  k++;
  matrix[k][0] = 6.9;
  matrix[k][1] = -0.06;
  k++;
  matrix[k][0] = 7.6;
  matrix[k][1] = 1.00;
  k++;
  matrix[k][0] = 8.0;
  matrix[k][1] = 0.00;
}

void fill(gsl_matrix *A, gsl_vector *b, double matrix[rows][2]) {
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      gsl_matrix_set(A, i, j, phi(j, matrix[i][0]));
    }
    gsl_vector_set(b, i, matrix[i][1]);
  }
}

double phi(int i, double value) {
  return binomial(max, i) * pow(value, i) * pow((1-value), (3-i));
}

double binomial(int n, int k) {
  if ((k == 0) || (k == n))
    return 1;
  if (k>n)
    return 0;

  return binomial(n - 1, k - 1) + binomial(n - 1, k);
}

void fill_codomain(gsl_vector *y, gsl_vector *x, double matrix[rows][2]) {
  for(int i = 0; i < y->size; i++) {
    gsl_vector_set(y, i, complete_phi(matrix[i][0], x));
  }
}

double complete_phi(double pos, gsl_vector *x) {
  double num = 0;
  for(int j = 0; j < x->size; j++) {
    num += gsl_vector_get(x, j)*phi(j, pos);
  }
  return num;
}

void fill_monomial(gsl_matrix *A, gsl_vector *b, double matrix[rows][2]) {
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      gsl_matrix_set(A, i, j, pow(matrix[i][0], j));
    }
    gsl_vector_set(b, i, matrix[i][1]);
  }
}

void fill_codomain_monomial(gsl_vector *y, gsl_vector *x, double matrix[rows][2]) {
  for(int i = 0; i < y->size; i++) {
    gsl_vector_set(y, i, sum_mu(matrix[i][0], x));
  }
}

double sum_mu(double x, gsl_vector *coef) {
  double sum = 0;

  for(int i = 0; i < coef->size; i++) {
    sum += gsl_vector_get(coef, i)*pow(x, i);
  }

  return sum;
}
