#include <stdio.h>
#include <stdlib.h>


/*
 * Layout (esempio ) interno:
 * '-' = 1 byte
 * 'P' = Padding
 *
 * +----+----+----+----+
 * |cPPP|num |den |abde|
 * +----+----+----+----+
 * 
 * le strutture hanno una lunghezza multipla del loro dato più lungo
 * quindi num e den, che sono di 4 byte, fanno in modo che anche c (1 byte) debba
 * occupare comunque altri 3 byte con un padding (sprecando spanzio).
 * Invece, abde, sono inseriti attaccati l'uno all'altro. Utilizzando tutti i 4 byte.
 *
 * Comunque la struttura che serve al codice ha solo num e den.
 * 
 */

struct fract {
   // unsigned char c; 
   int num;
   int den;
   /* esempio
   unsigned char a;
   unsigned char b;
   unsigned char d;
   unsigned char e;
   */ 
};

// crea una frazione con numeratore e denominatore
// restituisce NULL in out of memory, oppure restituisce la frazione
struct fract *create_fraction(int num, int den) {
  struct fract *f = malloc(sizeof(struct fract));
  if (f == NULL) return NULL; // malloc error checking
  f->num = num;
  f->den = den;
  return f;
}

void print_fraction(struct fract *f) {
  printf("%d/%d\n", f->num, f->den);
}


// semplifica la frazione 
void simplifly_fraction(struct fract *f) {
   for (int d = 2; d <=  f->num && d <= f->den; d++) {
      if (f->num % d == 0 &&
          f->den % d == 0) {
         f->num /= d;
         f->den /= d; 
      }
   }
}

int main(void) {
// | tipo     | nome
   struct fract a;
   struct fract *b = &a;
   a.num = 1;
   a.den = 2;
   printf("%d %d\n", a.num, a.den);
   b->num = 1; // se è un puntatore questa è la sintassi
   b->den = 2;
   printf("%d %d\n", b->num, b->den);
   

   struct fract *f1 = create_fraction(10, 20);
   struct fract *f2 = create_fraction(3, 4);
   simplifly_fraction(f1);
   print_fraction(f1);
   print_fraction(f2);
   return 0;
}
