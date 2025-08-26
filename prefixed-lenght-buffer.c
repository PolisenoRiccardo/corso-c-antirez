#include <stdio.h>
#include <stlib.h>

/* inizializza una prefixed lenght per una stringa specificata
 * in 'init' della lunghezza 'len' */
void ps_init(char *s, char *init, int len) {
   unsigned char *lenptr = (unsigned char*)s;
   *lenptr = len;
   for (int j = 0; j < *lenptr; j++) {
      s[j+1] = init[j];
   }
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

int main(void) {
  char buf[256]; // buffer
  ps_init(buf, "Hello World", 11); // ps = prefixed lenght string
  ps_print(buf);
  return 0; 
}
