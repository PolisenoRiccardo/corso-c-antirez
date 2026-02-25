#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Data structures */

#define TFOBJ_TYPE_INT 0
#define TFOBJ_TYPE_STR 1
#define TFOBJ_TYPE_BOOL 2
#define TFOBJ_TYPE_LIST 3
#define TFOBJ_TYPE_SYMBOL 4

typedef struct tfobj {
  int refcount;
  int type; // TFOBJ_TYPE_* (define)
  union {
    int i;
    struct str {
      char *ptr;
      size_t len;
    } str;
    struct list {
      struct tfobj **ele;
      size_t len;
    } list;  
  };
} tfobj;

typedef struct tfparser {
  char *prg; // the program to compile into a list
  char *p; // next token to parse

} tfparser;

typedef struct tfctx {
  tfobj *stack;
} tfctx;

/* ----------- Allocation Wrappers ----------------- */

void *xmalloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "Out of memory allocating %zu bytes\n", size);
    exit(1);
  }
  return ptr;
}


/* ----------- Object related functions ------------ */
/* These functions allocate different types */ 

tfobj *createObject(int type) {
  tfobj *o = xmalloc(sizeof(tfobj));
  o->type = type;
  o->refcount = 0;
  return o;
}

tfobj *createStringObject(char *s, size_t len) {
  tfobj *o = createObject(TFOBJ_TYPE_STR);
  o->str.ptr = s;
  o->str.len = len;
  return o;
}

tfobj *createSymbolObject(char *s, size_t len) {
  tfobj *o = createStringObject(s, len);
  o->type = TFOBJ_TYPE_SYMBOL;
  return o;
}


tfobj *createIntObject(int i) {
  tfobj *o = createObject(TFOBJ_TYPE_INT);
  o->i = i;
  return o;
}

tfobj *createBoolObject(int i) {
  tfobj *o = createObject(TFOBJ_TYPE_BOOL);
  o->i = i;
  return o;
}

tfobj *createListObject(int i) {
  tfobj *o = createObject(TFOBJ_TYPE_LIST);
  o->list.ele = NULL;
  o->list.len = 0;
  return 0;
}

/* Main */

int main(int argc,char **argv) {
  if (argc != 2) {
    printf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  return 0;
}
