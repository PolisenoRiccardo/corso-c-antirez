#include <stdio.h>

// errorcode diventa un alias di int
typedef int errorcode; 

typedef struct {
  int num;
  int den;
} fract;

typedef fract *fractptr;

int main(void) {
  errorcode a = -20;
  printf("%d\n", a);
  fract f;
  fractptr fp = &f; // non c'è bisogno dell'* 
  f.num = 10;
  f.den = 20;
  printf("%d/%d\n", f.num, f.den);
  return 0;
}
