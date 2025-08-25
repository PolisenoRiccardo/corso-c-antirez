#include <stdio.h>

int main(void) {
   int x = 5;
   int *y = &x; // 8 byte
   int **z = &y; // puntatore di un puntatore 
   printf("x is storedin %p and y is stored at %p\n", y, z);

   char mystr[] = "Hello World";
   char *p = mystr; // con gli array non serve la &, perché il solo nome dell'array  è il puntatore per l'array (??)

   printf("%c%c\n", p[0], p[1]); // stampa "He", è come scrimvere mystr[0] e mystr[1]
   printf("%c%c\n",*p, *(p+1)); // ... funziona allo stesso modo, visto che i puntatori sono interi, puoi sommarli

   char mynewstr[] = "AABBCCDDEEFF";
   short *pp = (short*)mynewstr; // il trasformatore di tipo non fa niente oltre silenziare il warning dopo la compilazione
   printf("%d\n", *pp); // stampa 16705 (AA in 16 bit (antirez fa 65+(65*256) = 16705, 256 perché 8 bit (2^8))
   pp++;
   printf("%d\n", *pp); // quando incremento un puntatore di 1, prima verrà moltiplicato
                        // per la grandezza del tipo base del puntatore (short in questo caso)
                        // quindi salta di coppia in coppia AA -> BB -> CC 
                        // NON AA -> AABB -> AABBCC. Perché è short.
   
   pp = (short*)mynewstr; // reset
   printf("%d\n", pp[0]); // come scrivere *p
   printf("%d\n", pp[1]); // come se avessi incrementato
   printf("%d\n", pp[4]); // come se avessi sommato 4 al puntatore
   // quindi si può sgravare con l'indice, uscendo dallo spazio di memoria di interesse oppure uscendo proprio dalla mermoria
  
   char *pl = mynewstr; // punta all'inizio dell'array

   printf("At the start pl is %p\n", pl);
   while (*pl != 0) { // le stringe finiscono con 0
      putchar(*pl);
      pl++; // qui non salta di coppia in coppia
            // è un char quindi prende ogni singolo carattere
   }
   printf("\n");
   printf("At the end pl is %p\n", pl);
   return 0;
}
