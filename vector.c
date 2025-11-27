#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define N 4
#define REPS 1000000

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
    if (i == n - 1) {
      printf("%.17g\n", z[i]);
    } else {
      printf("%.17g, ", z[i]);
    }
  }
}

double get_random(double max) {
  return ((double)rand() / (double)RAND_MAX) * max;
}

void benchmark() {
  srand(0);

  int n = 1048576;
  size_t bytes = n * sizeof(double);

  double* x1 = (double*)malloc(bytes);
  double* x2 = (double*)malloc(bytes);
  double* y1 = (double*)malloc(bytes);
  double* y2 = (double*)malloc(bytes);
  double* z = (double*)malloc(bytes);

  for (int i = 0; i < n; i++) {
    x1[i] = get_random(10.0);
    x2[i] = get_random(10.0);
    y1[i] = get_random(10.0);
    y2[i] = get_random(10.0);
  }

  printf("\n\nTEST CASE 2: Vectors of size %d (2^20) ran 10 times\n", n);
  printf("X1: ");
  print_vector(10, x1);
  printf("\nX2: ");
  print_vector(10, x2);
  printf("\nY1: ");
  print_vector(10, y1);
  printf("\nY2: ");
  print_vector(10, y2);

  printf("\nC implementation:\n");
  clock_t start = clock();
  for (int i = 0; i < 10; i++) {
    vector_dist_c(1048576, x1, x2, y1, y2, z);
  }
  clock_t end = clock();
  double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time taken: %f seconds\n", elapsed);
  printf("Value of Z: ");
  print_vector(10, z);

  printf("\n\nAssembly implementation:\n");
  start = clock();
  for (int i = 0; i < 10; i++) {
    vector_dist(1048576, x1, x2, y1, y2, z);
  }
  end = clock();
  elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time taken: %f seconds\n", elapsed);
  printf("Value of Z: ");
  print_vector(10, z);
}

int main() {
  double x1[N] = {1.5, 4.0, 3.5, 2.0};
  double x2[N] = {3.0, 2.5, 2.5, 1.0};
  double y1[N] = {4.0, 3.0, 3.5, 3.0};
  double y2[N] = {2.0, 2.5, 1.0, 1.5};

  double z[N] = {};

  printf("TEST CASE 1: Vectors of size %d ran 1 million times\n", N);
  printf("X1: ");
  print_vector(N, x1);
  printf("\nX2: ");
  print_vector(N, x2);
  printf("\nY1: ");
  print_vector(N, y1);
  printf("\nY2: ");
  print_vector(N, y2);
  printf("\n\n");

  printf("C implementation:\n");
  clock_t start = clock();
  for (int i = 0; i < REPS; i++) {
    vector_dist_c(N, x1, x2, y1, y2, z);
  }
  clock_t end = clock();
  double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time taken: %f seconds\n", elapsed);

  printf("Value of Z: ");
  print_vector(N, z);

  printf("\nAssembly implementation:\n");
  start = clock();
  for (int i = 0; i < REPS; i++) {
    vector_dist(N, x1, x2, y1, y2, z);
  }
  end = clock();
  elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time taken: %f seconds\n", elapsed);

  printf("Value of Z: ");
  print_vector(N, z);

  benchmark();

  return 0;
}