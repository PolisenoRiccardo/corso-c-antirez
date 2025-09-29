#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void) {
  char *mystr = "Hello World";
  size_t len = strlen(mystr);
  for (size_t j = 0; j < len; j++) {
    // STDOUT_FILENO è il file descriptor del terminale (già aperto)
    // 1 è il numero di byte che deve scrivere (imita putchar quindi 1 carattere)
    // write(STDOUT_FILENO, mystr+j, 1); <---------
    putchar(mystr[j]);
    fflush(stdout);
    usleep(100000); // millisecondi (effetto writing)
  }
  // i caratteri che dovrebbe scrivere la putchar vengono accumulati nel buffering finché 
  // non incontra una new line "\n" oppure fino al termine del programma
  // fflush forza la scrittura a prescindere dal comportamento standard della libc
  fflush(stdout); // stdout è un file descriptor
  // sleep è una funzione unix standard (quindi funziona su unix) 
  sleep(3);
  return 0;
}
