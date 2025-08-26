#include <stdio.h>
#include <stdlib.h>

int *create_fraction(int num, int den) {
  int *f = malloc(sizeof(int)*2);
  if (f == NULL) return NULL; // malloc error checking
  f[0] = num;
  f[1] = den;
  return f;
}

void print_fraction(int *f) {
  printf("%d/%d\n", f[0], f[1]);
}

int main(void) {
  int *f1 = create_fraction(10, 20);
  int *f2 = create_fraction(3, 4);
  print_fraction(f1);
  print_fraction(f2);
  return 0;
}
