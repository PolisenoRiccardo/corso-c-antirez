#include <stdio.h>

int main(void) {
	char c = 'a'; // il c gestisce solo i numeri
	printf("Hello World %d\n", c); // tradotto nel corrispondente valore ascii
	printf("%s\n", "Hello World"); // s: string
	printf("%c\n", 65); // stampa "A" (65 è l'ascii di A) | prints the ASCII representation of the character.
	
	int a[5] = {10, 5, 100, 7};
	printf("%d\n", a[0]);
	char str[6] = {'H', 'e', 'l', 'l', 'o', 0}; // Le stringhe sono questa roba qui | Lo 0 serve a indicare la fine della stringa
	
	// La printf esegue qualcosa di simile al codice sotto
	int i = 0;
	while(str[i] != 0) {
		printf("%c", str[i]);
		i++;
	}

	char essetierre[6] = "Hello"; // lunghezza di 6 e non di 5 per il terminatore 0
	printf("\n%s - %s\n", str, essetierre);

	char sixtyfive = 65;
	printf("c: %c, d: %d\n", sixtyfive, sixtyfive);
	return 0;
}
