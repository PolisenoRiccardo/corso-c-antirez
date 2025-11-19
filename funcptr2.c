#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

/* Funzione che definisce il criterio di ordinamento */
int compare_integers(const void *a, const void *b) {
  const int *ap = a;
  const int *bp = b;
  if (ap[0] > bp[0]) return 1;
  else if (ap[0] < bp[0]) return -1;
  else return 0;
}

int main(void) {
  int a[10];
  for (int i = 0; i < 10; i++) 
    /* & è una "maschera" 
     * operazione di bitwise AND 
     * 15 in binario è 1111, quindi confronta 
     * i bit del numero rand() e 15 
     * */ 
    a[i] = rand() & 15;
  
  a[2] = INT_MAX;
  a[5] = INT_MIN;
  /* qsort() richiede come parametro il puntatore ad una funzione che 
   * "fornisce" il criterio di ordinamento */
  qsort(a, 10, sizeof(int), compare_integers);
  
  for (int j = 0; j < 10; j++) 
    printf("%d ", a[j]);
  printf("\n");
  return 0;

}
