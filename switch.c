#include <stdio.h>

int main(void) {
   int i = 10;

   switch(i) {
   case 5: 
      printf("È un cinque\n"); 
      break; // senza il break continua ad eseguire le istruzioni successive
   case 7: 
      printf("È un sette\n"); 
      break; 
   default: 
      { 
         int blockin = 324;
         printf("È un altro numero %d\n", blockin); 
         break;
      }
   }
   return 0;
}
