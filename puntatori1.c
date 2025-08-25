#include <stdio.h>

void incr(int *p) {
   *p = *p + 1; // Dereferenziazione
}

int main(void) {
   int x = 4;
   int *y = NULL; // un puntatore, continua a chiamarsi y / 0 | NULL indirizzo nullo
                  // una variabile intera che contiene un indirizzo di memoria (largo come intptr_t, non come int) 
   printf("x was %d\n", x);

   y = &x; // la & richiede l'indirizzo di memoria della variabile indicata successivamente al simbolo
           // y ora vale come l'indirizzo di memoria in cui è contenuto x
   printf("x is stored at  %p\n", y);

   *y = 10; // salvo 10 nell'indirizzo a cui si riferisce y che è l'indirizzo in cui è salvata x
            // quindi cambia x 
   printf("x is %d\n", x);

   incr(y); // altra dimostrazione con l'utilizzo di una funzione

   printf("x incremented to %d\n",x);
   return 0;
}
