#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct pls {
  long len;
  char *str;
};

void hexdump(void *p, size_t len) { // void pointer devastante, del tipo "A cosa punti?", "Punto." 
  unsigned char *byte = p;
  for (size_t i = 0; i < len; i++ ) {
    printf("%02X ", byte[i]);
  }
  printf("\n");
}

int main(void) {
  struct pls s;

  s.len = 10;
  s.str = malloc(s.len+1); // +1 per il terminator
  memcpy(s.str, "1234567890", 11); // 11 è la lunghezza/spazio in byte
  printf("%ld\n", sizeof(s));
  printf("%p\n", s.str); // visualizza il puntatore in esadecimale (per confrontarlo con il risultato sotto
  hexdump(&s, sizeof(s)); // visualizza prima gli 8 byte dell'intero (0A 00 00 00 00 00 00 00) e poi del puntatore 
  return 0;
}
