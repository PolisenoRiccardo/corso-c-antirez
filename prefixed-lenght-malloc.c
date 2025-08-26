#include <stdio.h>
#include <stdlib.h>

/* inizializza una prefixed lenght per una stringa specificata
 * in 'init' della lunghezza 'len'
 */
char *ps_create(char *init, int len) {
   char *s = malloc(1+len);
   unsigned char *lenptr = (unsigned char*)s;
   *lenptr = len;
   for (int j = 0; j < *lenptr; j++) {
      s[j+1] = init[j];
   }
   return s;
}

// mostra la stringa 's'
void ps_print(char *s) {
   unsigned char *lenptr = (unsigned char*)s;
   int j = 0;
   while (j < *lenptr) {
      putchar(s[j + 1]);
      j++;
   }
   printf("\n");
}

// restituisce il puntatore al terminatore nullo delle stringe di c
char *ps_getc(char *s) {
   return s+1;
}

int main(void) {
   char *mystr = ps_create("Hello World", 11); // una stringa in un formato personalizzato 
   printf("Prefixed Lenght string: ");         // con la prefixed lenght
   ps_print(mystr); // ps = prefixed lenght string
   printf("C formatted string: %s\n", ps_getc(mystr));
   free(mystr);
   return 0; 
}
