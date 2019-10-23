#include <stdio.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_vector.h>

// Just a small test to see if GSL works ok.
void test() {
  double x = 5.0;
  double y = gsl_sf_bessel_J0(x);
  printf("J0(%g) = % .18e\n", x, y);
}

int main() {
    int n = 100;

    // Create right-hand side vector y
    gsl_vector * vector = gsl_vector_alloc (n);

    // First element of y at index 0 should be 1
    gsl_vector_set(vector, 0, 1);

    // Then fill with zeros
    for (int i = 1; i < n; i++) {
      gsl_vector_set(vector, i, 0);
    }

    // Print contents of the vector
    for (int i = 0; i < n; i++) {
      printf ("v_%d = %g\n", i, gsl_vector_get (vector, i));
    }

    return 0;
}