#include <stdio.h>
#include <math.h>

#define N 4

int main() {
  double x1[N] = {1.5, 4.0, 3.5, 2.0};
  double x2[N] = {3.0, 2.5, 2.5, 1.0};
  double y1[N] = {4.0, 3.0, 3.5, 3.0};
  double y2[N] = {2.0, 2.5, 1.0, 1.5};

  double z[N] = {};

  for (int i = 0; i < N; i++) {
    double dx = x2[i] - x1[i];
    double dy = y2[i] - y1[i];
    z[i] = sqrt(dx * dx + dy * dy);
  }

  for (int i = 0; i < N; i++) {
    printf("%.17g, ", z[i]);
  }

  return 0;
}