#include <ctype.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define HEXDUMP_CHARS_PER_LINE 16
void hexdump(void *p, size_t len) { // void pointer devastante, del tipo "A cosa punti?", "Punto." 
  unsigned char *byte = p;
  size_t j = 0;
  for (size_t i = 0; i < len; i++ ) {
    printf("%02X ", byte[i]);
    char is_last_line = i+1 == len;
    if ( (i+1) %  HEXDUMP_CHARS_PER_LINE == 0  || is_last_line) { // torna a capo ogni tot byte
      if (is_last_line) {
        int pad = HEXDUMP_CHARS_PER_LINE -(len % HEXDUMP_CHARS_PER_LINE);
        pad %= HEXDUMP_CHARS_PER_LINE;
        for (int j = 0; j < pad; j++) 
          printf("   ");
      }
      printf("\t"); // tab - spostamento a destra 
      // a fianco di ogni riga vengono stampati i caratteri corrispondenti stampabili
      while (j <= i) {
        int c = isprint(byte[j]) ? byte[j] : '.'; // se isprint() è vera, c = byte[j], altrimenti c = '.'
        printf("%c", c);
        j++;
      }
      printf("\n");
    }   
  }
}

int main(void) {
  // fd: file descriptor 
  // open è una chiamata di sistema diretta (fopen utilizza open, è un wrapper)
  int fd = open("stdio1_system_calls.c", O_RDONLY); 
  // se open restituisce -1 significa errore
  if (fd == -1) {
    // perror aggiunge alla stringa il testo corrispondente al tipo di errore
    perror("Unable to open file");
    return 1;
  }
  
  char buf[32];
  // size_t ma signed, perché read può restituire -1 (devo chiarire perché non ho capito)
  ssize_t nread;
  while (1) {
    // read differisce da fread nell'ordine degli argomenti
    // non richiede la lunghezza (anche qui non so esattamente di cosa sto parlando)
    nread = read(fd, buf, sizeof(buf)); 
    if (nread == 0) break;
    hexdump(buf, nread);
  }
  
  // anche close è una chiamata di sistema, non legata ad open
  // close è generico, infatti è nella libreria unistd.h
  close(fd);
  return 0;
}
