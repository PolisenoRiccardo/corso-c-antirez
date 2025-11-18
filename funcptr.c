#include <stdio.h>

void ciao() {
  printf("Ciao\n");
}

/* void (*func)(void) 
 * void = il tipo della funzione
 * (*func) = il puntatore alla funzione
 * (void) = gli argomenti accettati dalla funzione
 *
 * (*func) è semplificabile scrivendo solo func, il compilatore
 * lo legge allo stesso modo, visto che i nomi delle funzioni sono puntatori
 * a se stessi. Per chiarezza e leggibilità preferisco scrivere l'asterisco.
  */
void ripeti_n_volte(int n, void (*func)(void)) {
  /* il while controlla se n è zero prima di decrementarlo 
   * per poi decrementarlo */
  while (n--)  
    /* viene chiamata la funzione */
    func(); 
}

int main(void) {
  printf("main at %p\n", main); // I nomi delle funzioni sono puntatori
  ripeti_n_volte(10, ciao);
  return 0;
}
