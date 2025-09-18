#include <ctype.h>
#include <stdio.h>

#define HEXDUMP_CHARS_PER_LINE 16
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
  FILE *fp = fopen("stdio1.c", "r"); // r = legge il file una volta
  if (fp == NULL) {
    printf("Unable to open file\n");
    return 1;
  }
  char buf[32];
  size_t nread;
  while (1) {
    nread = fread(buf, 1, sizeof(buf), fp);
    if (nread == 0) break;
    hexdump(buf, nread);
  }
  fclose(fp); // necessario per evitare il memory leak
}
