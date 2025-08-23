#include <stdio.h>

/*
 hexdump -C su unix mostra il dump canonico in esadecimale
 antirez fa clear | hexdump -C
 */

void clear(void) {
	printf("\x1b[H"); 
	// dovrebbe fare il clear ma accadono cose strane
	// H significa Home e fa andare il cursore alla prima riga del terminale, infatti si sovrappone al testo già stampatoi
	printf("\x1b[2J\x1b[H");
	// ora funziona
}

int main(void) {
	clear();
	printf("Hello World\n");
	return 0;
} 
