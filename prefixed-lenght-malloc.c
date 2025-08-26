#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/* inizializza una prefixed length per una stringa specificata
 * in 'init' della lunghezza 'len'
 */
char *ps_create(char *init, int len) {
   char *s = malloc(4+len+1);
   uint32_t *lenptr = (uint32_t*)s;
   *lenptr = len;
   
   s += 4;
   for (int j = 0; j < len; j++) {
      s[j] = init[j]; // dovremmo usare memcopy()
   }
   s[len] = 0;
   return s;
}

// mostra la stringa 's'
void ps_print(char *s) {
   uint32_t *lenptr = (uint32_t *)(s-4);
   uint32_t j = 0;
   while (j < *lenptr) {
      putchar(s[j]);
      j++;
   }
   printf("\n");
}

// mostra la lunghezza della stringa 's'
uint32_t ps_len(char *s) {
   uint32_t *lenptr = (uint32_t *)(s-4);
   return *lenptr;
}


// libera una stringa pl creata precedentemente
void ps_free(char *s) {
   free(s-4);
}

char *global_string;

int main(void) {
   char *mystr = ps_create("Hello World", 11); // una stringa in un formato personalizzato 
   global_string = mystr;
   printf("Prefixed Lenght string: ");         // con la prefixed lenght
   ps_print(mystr); // ps = prefixed length string
   printf("C formatted string: %s, String Lenght: %d\n", mystr, ps_len(mystr));
   ps_free(mystr);
   printf("%s\n", global_string);
   return 0; 
}
