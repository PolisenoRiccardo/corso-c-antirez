#include <stdio.h>

void conta(int start, int end) {
   if (start > end) return; // uscita
   printf("ricorsione %d [ %p ] )\n", start, &start);
   conta(start+1, end);

   // questo metodo è tremendo a quanto pares
   // le funzioni annidate consumano molta memoria
   // si accumulano sulla pila
}

void conta_meglio(int start, int end) {
iterate:
   if (start > end) return;
   printf("iterazione %d [ %p ] )\n", start, &start);
   start++;
   goto iterate;
}

int main(void) {
   int i = 0;

   // again è un'etichetta, deve iniziare con una lettera
again: 
      printf("i %d\n", i);
      i++;
      if (i < 10) goto again;

   // while! 
   int w = 0;
   while (w < 10) {
      printf("w %d\n", w);
      w++;
   }

   // come il compilatore gestisce il while 
   int ifloop = 0;
loop:
   if (ifloop < 10) goto enter_loop;
   goto next;
enter_loop:
   printf("ifloop %d\n",ifloop);
   ifloop++;
   goto loop;
next:

   // metodo ricorsione
   conta(0, 9);

   printf("\n"); 

   // metodo iterazione goto
   conta_meglio(0, 9);

   return 0;

}



