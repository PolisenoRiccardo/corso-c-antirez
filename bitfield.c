#include <stdio.h>
#include <string.h>
#include <limits.h>

struct foo {
  /* Definisce quanti bit (come limite) occupano le variabili.
   * Potrebbero derivare dei problemi a seconda dell'architettura della macchina.
   * Esempio di utilizzo: Header di un protocollo (come l'IP) */
  int a:4;
  int b:4;
  int c:8;
};

int main(void) {
  return 0;
}
