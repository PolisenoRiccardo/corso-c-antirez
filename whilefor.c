#include <stdio.h>

int main(void) {
   
   // di seguito due metodi con la stessa funzione e funzionamento
   // entrambi hanno l'inizializzazione (i = 0) la condizione (i < 10) e l'incremento (i++)

   int i = 0; // salvatore consiglia di dichiarare la variabile esternamente 
              // in modo da poterla utilizzare anche fuori dal loop
   for (i = 0; i < 10; i++) {
      printf("for %d\n", i);
   }

   printf("\n");

   i = 0;
   while (i < 10) {
      printf("while %d\n", i);
      i++;
   }
   
   //esempi per mostrare le uguaglianze   

   // for infinito
   i = 0;
   for (;;) {
      if (i>=10) break;
      printf("%d\n", i);
      i++;
   }

   //while infinito
   i = 0;
   while (1) {
      if (i>=10) break;
      printf("%d\n", i);
      i++;
   }

   return 0;
}
