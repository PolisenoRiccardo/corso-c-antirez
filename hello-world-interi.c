#include <stdio.h>
#include <limits.h>
#include <stint.h> // permette di specificare la grandezza desiderata 

int main(void) {
	// intptr_t // ptr sta per pointer // antirez fa un discorso interessante sulla sottrazione tra i puntatori, per conoscere se un puntatore è precedente ad un altro (ptr1 - ptr2 se risulta negativo ptr2 è successivo a ptr1)
	// uint64_t // unsigned int da 64 bit
	// int64_t // un int da 64 bit a quanto pare non avrà problemi di overflow 
	// size_t // maximum size of any object  
	char c = 1; // interno 8 bit
	short s = 2000; // 16 bit
	int x = 5; // 32 bit
	long l = 10; // 64 bit -> Di solito è pari alla quantità di bit del processore 
	// lu: long unsigned
	// sizeof() restituisce un long unsigned
	printf("Hello World: int min: %d, int max: %d\n sizeof: %lu", INT_MIN, INT_MAX, sizeof(x);
	return 0;
}
