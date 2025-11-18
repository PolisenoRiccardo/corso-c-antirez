#include <stdio.h>
#include <string.h>

struct foo {
  /*
   * L'union fa coincidere lo stesso indirizzo di memoria 
   * ai suoi elementi. È utile per risparmiare spazio dedicando allo stesso indirizzo
   * diversi campi che non vorrebbero usate contemporaneamente (esempio del token nella 
   * ricerca vettoriale in redis)
   */
  union {
    int i;
    unsigned char a[4];
  };
};

int main(void) {
  struct foo f;
  f.i = 10;
  printf("%d [%d %d %d %d]\n", f.i, f.a[0], f.a[1], f.a[2], f.a[3]);
  /* Output: 10 [10 0 0 0]
   * Nelle [...] è rappresentato il valore in byte
   * (il 10 è in prima posizione e non in ultima per il sistema little-endian)
   * Si osserva la sovrascrittura del valore f.a[0] e f.i coincidono per l'union
   * */
  return 0;
}
