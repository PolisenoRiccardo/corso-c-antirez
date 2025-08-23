#include <stdio.h>

int main(void) {

   // non conosco niente 
   // il basic in c? 
   // neanche lo conosco il basic ma figo
   // il concetto è che è possibile con goto eseguire la riga definita (l10 in questo caso)
   // in Basic non c'è la l prima del numero, in c serve per la sintasse dell'etichetta

   l10: printf("EH?!\n");
   l20: goto l10;

   return 0;
}
