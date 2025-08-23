#include <stdio.h>

int main(void) {
	int i = 5;

	if (i > 3) {
		printf("i > 3\n");	
	} else {
		printf("i > 3\n");
	}

	if (i > 3) printf("i > 3\n"); // semplifica la quantità di righe e quindi | funziona senza {...}  (chiamato blocco) se c'è un solo statement
	int e = 401;
	
	{
		int i = 54; // la i essendo locale è una i diversa
		printf("i is %d\ne is %d\n", i, e); 
	}
	printf("i is %d\n", i);

	return 0;
	
}
