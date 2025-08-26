#include <stdio.h>

int main(void) {
   char str[] = "\017Hello00\0000000123"; // \017 (15) prefixed lenght 
   char *p = str;
   printf("My string len is %d\n", p[0]); 
   int len = *p++; // la precedenza degli operatori permette di inizializzare len con *p 
                   // e poi incrementare p
   for (int j = 0; j < len; j++) {
      putchar(p[j]);
   }
   printf("\n");
}
