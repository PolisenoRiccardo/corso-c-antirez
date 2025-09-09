#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct pls {
  long len;
  char str[20];
};

#define HEXDUMP_CHARS_PER_LINE 8
void hexdump(void *p, size_t len) { // void pointer devastante, del tipo "A cosa punti?", "Punto." 
  unsigned char *byte = p;
  size_t j = 0;
  for (size_t i = 0; i < len; i++ ) {
    printf("%02X ", byte[i]);
    char is_last_line = i+1 == len;
    if ( (i+1) %  HEXDUMP_CHARS_PER_LINE == 0  || is_last_line) { // torna a capo ogni tot byte
      if (is_last_line) {
        /* tentativo mio prima di vedere la soluzione di antirez
        size_t k = i;
        while ((k+1) % HEXDUMP_CHARS_PER_LINE != 0) { 
          printf("   ");
          k++;
        }*/
        int pad = HEXDUMP_CHARS_PER_LINE -
          (len % HEXDUMP_CHARS_PER_LINE);
        pad %= HEXDUMP_CHARS_PER_LINE;
        for (int j = 0; j < pad; j++) printf("   ");
      }
      printf("\t"); // tab - spostamento a destra 
      // a fianco di ogni riga vengono stampati i caratteri corrispondenti stampabili
      while (j <= i) { // antirez usa una variabile "po" per memorizzare lo stato di j fuori dal ciclo for
                       // ma ho pensato di utilizzare un while e dichiarare j fuori dal ciclo, 
                       // per il gusto di farlo diversamente.
        int c = isprint(byte[j]) ? byte[j] : '.'; // se isprint() è vera, c = byte[j], altrimenti c = '.'
        printf("%c", c);
        j++;
      }
      printf("\n");
    }   
  }
}

int main(void) {
  struct pls s;

  // memset(&s, 0xff, sizeof(s));
  // riempie per la size della struttura il valore 0xff (255)
  // rispetto al memcpy imposta un unico valore (il secondo argomento)

  s.len = 10;
  memcpy(s.str, "1234567890", 11); // 11 è la lunghezza/spazio in byte
  printf("%ld\n", sizeof(s));
  printf("%p\n", s.str); // visualizza il puntatore in esadecimale (per confrontarlo con il risultato sotto
  hexdump(&s, sizeof(s)-3); // visualizza prima gli 8 byte dell'intero (0A 00 00 00 00 00 00 00) e poi del puntatore 
  return 0;
}
