#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct pls {
   uint32_t len;
   uint32_t refcount;
   uint32_t magic;
   char str[]; 
};

/* inizializza una prefixed length per una stringa specificata
 * in 'init' della lunghezza 'len'
 */
char *ps_create(char *init, int len) {
   struct pls *p = malloc(sizeof(struct pls)+len+1); // 4 string lenght bytes
                              // len string bytes
                              // 1 terminator byte
   p->len = len; 
   p->refcount = 1; 
   p->magic = 0xDEADBEEF; // serve alla validazione

   for (int j = 0; j < len; j++) {
      p->str[j] = init[j]; // dovremmo usare memcopy()
   }
   p->str[len] = 0; // impostazione del terminatore
   return p->str;
}

// mostra la stringa 's'
void ps_print(char *s) {
  struct pls *p = (struct pls*)(s - sizeof(*p)); 
   uint32_t j = 0;
   while (j < p->len) {
      putchar(p->str[j]);
      j++;
   }
   printf("\n");
}

// mostra la lunghezza della stringa 's'
uint32_t ps_len(char *s) {
   struct pls *p = (struct pls*)(s - sizeof(*p)); 
   return p->len;
}


// libera una stringa pl creata precedentemente
void ps_free(char *s) {
   free(s-sizeof(struct pls)); // sottraggo ad s la sua grandezza perché il puntatore dato
                               // come argomento a free deve essere al suo inizio (come quando inizializzato 
                               // con malloc()
}


// valida l'esistenza della stringa nella memoria,
// senza il controllo, non funzionava, 
// il refcount non rispettava il suo vero valore una volta sotto lo zero 
void ps_validate(struct pls *p) {   
   if  (p->magic != 0xDEADBEEF) {
     printf("INVALID STRING: Aborting\n");
     exit(1);
   }
}

// decrementa il refcount e libera l'oggetto se il refcount è a 0
void ps_release(char *s) {
   struct pls *p = (struct pls*)(s - sizeof(*p));
   
   ps_validate(p);


   p->refcount--;
   if (p->refcount == 0) {
     p->magic = 0;
     ps_free(s);
   }
}

// incrementa il refcount della stringa
void ps_retain(char *s) {
   struct pls *p = (struct pls*)(s - sizeof(*p));
   if (p->refcount == 0) {
      printf("ABORTED ON RETAIN OF ILLEGAL STRING\n");
      exit(1);
   }
   p->refcount++; 
}

char *global_string;

int main(void) {
   char *mystr = ps_create("Hello World", 11); // una stringa in un formato personalizzato 
   global_string = mystr;
   ps_retain(mystr);

   printf("Prefixed Lenght string: ");         // con la prefixed lenght
   ps_print(mystr); // ps = prefixed length string
   printf("C formatted string: %s, String Lenght: %d\n", mystr, ps_len(mystr));
   ps_release(mystr);
   printf("%s\n", global_string);
   ps_release(mystr);
   ps_release(mystr);
   return 0; 
}
