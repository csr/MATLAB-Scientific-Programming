#include <stdio.h>
#include "gsl/gsl_sf_gamma.h"
#include "gsl/gsl_sf_pow_int.h"

double calculateBinomialCoefficient(int n, int k) {
  // formula: (n k) = n! / (k!(n-k))
  double numerator = gsl_sf_fact(n);
  double denominator = gsl_sf_fact(k)*gsl_sf_fact(n-k);
  return numerator/denominator;
}

double calculateFunction(int i, double x) {
  double binomialCoefficient = calculateBinomialCoefficient(3, i); // (3 i)
  double secondTerm = gsl_sf_pow_int(x, i); // x^i
  double thirdTerm = gsl_sf_pow_int(1-x, 3-i);
  return binomialCoefficient*secondTerm*thirdTerm;
}

int main() {
  double x[] = {0.0, 0.6, 1.5, 1.7, 1.9, 2.1, 2.3, 2.6, 2.8, 3.0, 3.6, 4.7, 5.2, 5.7, 5.8, 6.0, 6.4, 6.9, 7.6, 8.0};
  double y[] = {-0.80, -0.34, 0.59, 0.59, 0.23, 0.10, 0.28, 1.03, 1.50, 1.44, 0.74, -0.82, -1.27, -0.92, -0.92, -1.04, -0.79, -0.06, 1.00, 0.00};

  printf("j . x_j . y_j\n");
  for (int i = 0; i < sizeof(x)/sizeof(x[0]); i++) {
    printf("%d & %.1f & %.2f\\\\\n", i, x[i], y[i]);
  }

  // Basis functions
  for (int i = 0; i < 4; i++) {
    double functionOutput = calculateFunction(i, 2);
    printf("Calculating function for i (%d): %lf\n", i, functionOutput);
  }

  double n = 40.0;
  double k = 3.0;
  printf("Binomial coefficient of %lf and %lf: %lf\n", n, k, calculateBinomialCoefficient(n, k));
  return 0;
}