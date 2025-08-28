#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * codice che imita il funzionamente del comando tac nella shell unix
 * tac visualizza al contrario il contenuto del file specificato (cat al contrario)
 *
 * come argomenti di una funzione: 
 * char **argv == char *argv[], 
 * char arr[] == char *arr
 *
 */

struct line {
   char *s;
   struct line *next;
};

int main(int argc, char **argv) {
   if (argc != 2) {
      printf("Missing file name.\n");
      return 1;
   }
   
   FILE *fp = fopen(argv[1], "r"); // apre il file
                                   // ogni argomento nella shell è un elemento, 
                                   // il primo è il comando e il secondo è il file.
                                   // quindi argv[1]
                                   // apre il file in read only "r"
   if (fp == NULL) {
      printf("File does not exist.\n");
      return 1;
   }

   char buff[1024];
   struct line *head = NULL;
   while (fgets(buff, sizeof(buff), fp) != NULL) {
      struct line *l = malloc(sizeof(struct line));
      size_t linelen = strlen(buff);
      l->s =malloc(strlen(buff)+1);
      for (size_t j = 0; j <= linelen; j++) {
         l->s[j] = buff[j];
      }
      l->next = head;
      head = l;
   } 

   fclose(fp);

   while (head != NULL) {
      printf("%s", head->s);
      head = head -> next;
   }
   return 0;
}
