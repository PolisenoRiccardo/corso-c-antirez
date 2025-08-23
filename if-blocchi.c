#include <stdio.h>

int main(void) {
	int i = 5;

	if (i > 3) {
		printf("i > 3\n");	
	} else {
		printf("i > 3\n");
	}

	if (i > 3) printf("i > 3\n"); 
   // semplifica la quantità di righe 
   // funziona anche senza {...} se c'è un solo statement

   // blocchi 

   int e = 401; 	
	{
		int i = 54; // la i essendo locale è una i diversa
		printf("i is %d\ne (%p) is %d\n", i, &e,e);

      e = 3; // registro A
      int e = 4; // registro B (diverso)

      printf("e (%p) is %d\n", &e,e);
    
      printf("i (%lu bytes) is stored at %p\n", sizeof(i),&i);
	}

   printf("i is %d\n", i);

   printf("i (%lu bytes) is stored at %p\n", sizeof(i),&i);
   // sono registrate in registri diversi (distanti di 4 byte e sono grandi 4 byte)

	return 0;
	
}
