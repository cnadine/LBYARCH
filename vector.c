#include <stdio.h>
#include <math.h>
#include <time.h>

#define N 4

extern void vector_dist(int n, const double* x1, const double* x2, const double* y1, const double* y2, double* z);

void vector_dist_c(int n, const double* x1, const double* x2, const double* y1, const double* y2, double* z) {
  for (int i = 0; i < n; i++) {
    double dx = x2[i] - x1[i];
    double dy = y2[i] - y1[i];
    z[i] = sqrt(dx * dx + dy * dy);
  }
}

void print_vector(int n, const double* z) {
  for (int i = 0; i < n; i++) {
    printf("%.17g, ", z[i]);
  }
}

int main() {
  double x1[N] = {1.5, 4.0, 3.5, 2.0};
  double x2[N] = {3.0, 2.5, 2.5, 1.0};
  double y1[N] = {4.0, 3.0, 3.5, 3.0};
  double y2[N] = {2.0, 2.5, 1.0, 1.5};

  double z[N] = {};

  printf("C implementation:\n");
  clock_t start = clock();
  vector_dist_c(N, x1, x2, y1, y2, z);
  clock_t end = clock();
  double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time taken: %f seconds\n", elapsed);

  print_vector(N, z);

  printf("\n\nAssembly implementation:\n");
  start = clock();
  vector_dist(N, x1, x2, y1, y2, z);
  end = clock();
  elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time taken: %f seconds\n", elapsed);

  print_vector(N, z);

  return 0;
}