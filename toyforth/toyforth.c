#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

/* Data structures */

#define TF_OK 0
#define TF_ERR 1

#define TFOBJ_TYPE_INT 0
#define TFOBJ_TYPE_STR 1
#define TFOBJ_TYPE_BOOL 2
#define TFOBJ_TYPE_LIST 3
#define TFOBJ_TYPE_SYMBOL 4
#define TFOBJ_TYPE_ALL 255

typedef struct tfobj {
  int refcount;
  int type; // TFOBJ_TYPE_* (define)
  union {
    int i;
    struct {
      char *ptr;
      size_t len;
      int quoted; // True or False
    } str;
    struct {
      struct tfobj **ele;
      size_t len;
      size_t alloc_en; 
    } list;  
  };
} tfobj;

typedef struct tfparser {
  char *prg; // the program to compile into a list
  char *p; // next token to parse

} tfparser;

/* Function table entry: each entry represents a symbol name
 * associated with a function implementation. */
struct tfctx;  /* forward declaration: callbacks can mention tfctx */

/* Function table entry: each entry represents a symbol name
 * associated with a function implementation. */
struct tfctx;  /* forward declaration: callbacks can mention tfctx */

typedef struct FunctionTableEntry {
  tfobj *name;
  int (*callback) (struct tfctx *ctx, char *name);
  tfobj *user_func;
} tffuncentry;

typedef struct FunctionTable {
  tffuncentry **func_table;
  size_t func_count;
} FunctionTable;

typedef struct tfctx {
  tfobj *stack;
  FunctionTable functable;
} tfctx;

/* ============ Prototypes =================== */

void retain(tfobj *o);
void release(tfobj *o);

/* ----------- Allocation Wrappers ----------------- */

void *xmalloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "Out of memory allocating %zu bytes\n", size);
    exit(1);
  }
  return ptr;
}

void *xrealloc(void *oldptr, size_t size) {
  void *ptr = realloc(oldptr, size);
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
  o->refcount = 1;
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

void retain(tfobj *o) {
  o->refcount++;
}

void free_object(tfobj*);

void release(tfobj *o) {
  assert(o->refcount > 0);
  o->refcount--;
  if (o->refcount == 0) free_object(o);
}

void free_object(tfobj *o) {
  switch (o->type) {
  case TFOBJ_TYPE_LIST:
    for (size_t i = 0; i < o->list.len; i++)
    {
        tfobj *ele = o->list.ele[i];
        release(ele); // non free
    } 
    break;
  case TFOBJ_TYPE_SYMBOL:
  case TFOBJ_TYPE_STR:
    free(o->str.ptr);
    break;
  default:
    break;
  }
  free(o);
}


void print_object(tfobj *o) {
  switch (o->type) {
  case TFOBJ_TYPE_INT:
    printf("%d", o->i);
    break;
  case TFOBJ_TYPE_LIST:
    printf("[");
    for (size_t i = 0; i < o->list.len; i++)
    {
        tfobj *ele = o->list.ele[i];
        print_object(ele);
        if (i != o->list.len-1) 
          printf(" ");
    } 
    printf("]\n");
    break;
  case TFOBJ_TYPE_STR:
    printf("\"%s\"", o->str.ptr);
    break;
  case TFOBJ_TYPE_SYMBOL:
    printf("%s", o->str.ptr);
    break;
  default:
    printf("?");
    break;
  }
}

/* ================ String object ================ */

tfobj *createStringObject(char *s, size_t len) {
  tfobj *o = createObject(TFOBJ_TYPE_STR);
  o->str.ptr = xmalloc(len+1);
  o->str.len = len;
  memcpy(o->str.ptr, s, len);
  o->str.ptr[len] = 0;
  return o;
}

tfobj *createSymbolObject(char *s, size_t len) {
  tfobj *o = createStringObject(s, len);
  o->type = TFOBJ_TYPE_SYMBOL;
  return o;
}

/* Compare the two string objects a and b, return 0 if they are 
* the same, 1 if a>b, -1 if a<b. The comparison i s performed
* using memcmp(). */
int compareStringObject(tfobj *a, tfobj *b) {
  size_t minlen = a->str.len < b->str.len ? a->str.len : b->str.len;
  int cmp = memcmp(a->str.ptr, b->str.ptr, minlen);
  
  if (cmp == 0) {
    if (a->str.len == b->str.len) return 0;
    else if (a->str.len > b->str.len) return 1;
    else return -1;
  } else {
    if (cmp < 0) return -1;
    else return 1;
  }
}
/* ================ List object ================ */

tfobj *createListObject(void) {
  tfobj *o = createObject(TFOBJ_TYPE_LIST);
  o->list.ele = NULL;
  o->list.len = 0;
  return o;
}

// adds element at the and of the list
// it is up to the callor to increment the refcount
void listPush(tfobj *l, tfobj *ele)  {
  l->list.ele = xrealloc(l->list.ele, sizeof(tfobj*) * (l->list.len + 1));
  l->list.ele[l->list.len]= ele;
  l->list.len++;
};

tfobj *listPopType(tfctx *ctx, int type) {
  tfobj *stack =  ctx->stack;
  if (ctx->stack->list.len == 0) return NULL;
  tfobj *to_pop = ctx->stack->list.ele[ctx->stack->list.len-1];
  if (to_pop->type != type && type != TFOBJ_TYPE_ALL) return NULL;
  stack->list.len--;
  if (stack->list.len == 0) {
    free(stack->list.ele);
    stack->list.ele = NULL;
  }
  stack->list.ele = xrealloc(stack->list.ele, sizeof(tfobj*) * stack->list.len);
  return to_pop;
}

tfobj *listPop(tfctx *ctx) {
  return listPopType(ctx, TFOBJ_TYPE_ALL);
}

/* ================== Compile ================= */

#define MAX_NUM_LEN 128
tfobj *parseNumber(tfparser *parser) {
  char buf[MAX_NUM_LEN];
  char *start = parser->p;
  char *end;
  if (parser->p[0] == '-') parser-> p++;
  while (parser->p[0] && isdigit(parser->p[0])) parser->p++;
  end = parser->p;
  int numlen = end-start;
  if (numlen >= MAX_NUM_LEN) return NULL;

  memcpy(buf, start, numlen);
  buf[numlen] = 0;

  tfobj *o = createIntObject(atoi(buf));
  return o;
}

// Returns true if "c" is an acceptable symbol
int is_symbol_char(int c) {
    char symchars[] = "+-*/%";
    // chad return isalpha(c) || strchr(symchars,c) != NULL;
    if (isalpha(c))  { 
      return 1;
    } else if (strchr(symchars,c) != NULL) {
      return 1; 
    } else {
      return 0;
    }
}

tfobj *parseSymbol(tfparser *parser) {
    char *start = parser->p;
    while (parser->p[0] && is_symbol_char(parser->p[0])) parser->p++;
    int len = parser->p - start;
    return createSymbolObject(start, len);
}

void parseSpaces(tfparser *parser) {
  while (isspace(parser->p[0])) parser->p++;
}

tfobj *compile(char *prg) {
  tfparser parser ;
  parser.prg = prg;
  parser.p = prg;

  tfobj *parsed = createListObject();

  while (parser.p) {
    tfobj *o;
    char *token_start = parser.p;

    parseSpaces(&parser);
    if (parser.p[0] == 0) break; // end
    if (isdigit(parser.p[0]) || (parser.p[0] == '-' && isdigit(parser.p[1]))) {
      o = parseNumber(&parser);
    } else if (is_symbol_char(parser.p[0])) {
      o = parseSymbol(&parser);
    } else {
      o = NULL;
    }

    // Check error
    if (o == NULL) {
      release(parsed);
      printf("Syntax error near: %32s ...\n", token_start);
      return NULL;
    } else {
      listPush(parsed, o); // push element
    }
    
  }
  return parsed;
}

int basicMathFunctions(tfctx *ctx, char *name);

/*==================== Execution and context =========================*/

int ctxCheckStackMinLen(tfctx *ctx, int min) {
  return (ctx->stack->list.len < (size_t) min) ? TF_ERR : TF_OK;
}

/* Pop the top element from the interpreter main stack, assuming it
* will match 'type', otherwise NULL is returned. Also the function
* returns NULL if the stack is  empty. 
* 
* The reference counting of the popped object is not modified: it
* is assumed that we just transfer the ownership from the stack to
* the caller.*/

tfobj *ctxStackPop(tfctx *ctx, int type) {
  return listPopType(ctx, type);
}

/* Push the object one the interpreter main stack */
void ctxStackPush(tfctx *ctx, tfobj *obj) {
  listPush(ctx->stack, obj);
}

/* Resolve the funcion scanning the function table lookgin for
* a matching name. If a matching function was not fount, NULL is returned,
* otherwhise the function returns the function entry object*/
tffuncentry *getFunctionByName(tfctx *ctx, tfobj *name) {
  for (size_t j = 0; j < ctx->functable.func_count; j++) {
    tffuncentry *fe = ctx->functable.func_table[j];
    if (compareStringObject(fe->name, name) == 0) return fe;
  }
  return NULL;
}
/* Push a new function entry in the context, it's up to
* the caller to set the C callback or the list representing the user
* defined function */
tffuncentry *registerFunction(tfctx *ctx, tfobj *name) {
  ctx->functable.func_table = 
      xrealloc(ctx->functable.func_table,
            sizeof(tffuncentry*) * (ctx->functable.func_count+1));
  tffuncentry *fe = xmalloc(sizeof(tffuncentry));
  ctx->functable.func_table[ctx->functable.func_count] = fe;
  ctx->functable.func_count++;
  fe->name = name;
  retain(name);
  fe->callback = NULL;
  fe->user_func = NULL;
  return fe;
}


/* Register a new function with a given name in the function table
* of the context. The function can't fail since if a function with the
* same name already exixts, it gets replaced by the new one */
void registerCFunction(tfctx *ctx, char *name, 
                        int (*callback) (tfctx *ctx, char *name)) {
  tffuncentry *fe;
  tfobj *oname = createStringObject(name, strlen(name));
  fe = getFunctionByName(ctx, oname);
  if (fe) {
    if (fe->user_func) {
        release(fe->user_func);
        fe->user_func = NULL;
      } 
    fe->callback = callback;
  } else {
    fe = registerFunction(ctx, oname);
    fe->callback = callback;
  }
  release(oname);
}

tfctx *create_context(void) {
  tfctx *ctx = xmalloc(sizeof(*ctx));
  ctx->stack = createListObject();
  ctx->functable.func_table = NULL;
  ctx->functable.func_count = 0;
  registerCFunction(ctx, "+", basicMathFunctions);
  return ctx;
}

/* Try to resolve and call the function associated with the symbol name 'word'.
 * Return 0 if the symbol was bound to some function and was executed, return 1 otherwise */
int call_symbol(tfctx *ctx, tfobj *word) {
  tffuncentry *fe = getFunctionByName(ctx, word);
  if (fe == NULL) return TF_ERR;
  if (fe->user_func) {
    // TODO
    return TF_ERR;
  } else {
    return fe->callback(ctx, fe->name->str.ptr);
  }
  return TF_OK; 
} 

int exec(tfctx *ctx, tfobj *prg) {
  assert(prg->type == TFOBJ_TYPE_LIST);
  for (size_t i = 0; i < prg->list.len; i++) {
    tfobj *word = prg->list.ele[i];
    switch (word->type) {
    case TFOBJ_TYPE_SYMBOL:
        if (call_symbol(ctx, word) == TF_ERR) {
            printf("Runtime error\n");
            return TF_ERR;
        }
      break;
    default:
      ctxStackPush(ctx, word);
      retain(word);
      break;
    }
  } 
  return TF_OK;
}

/*==================== Basic Standard Library =========================*/

int basicMathFunctions(tfctx *ctx, char *name) {
  if (ctxCheckStackMinLen(ctx, 2) == 1) return TF_ERR;
  tfobj *b = ctxStackPop(ctx, TFOBJ_TYPE_INT);
  tfobj *a = ctxStackPop(ctx, TFOBJ_TYPE_INT);
  if (a == NULL || b == NULL) return TF_ERR;
  int result;
  switch (name[0]) {
    case '+': result = a->i + b->i; break;
    case '-': result = a->i - b->i; break;
    case '*': result = a->i * b->i; break;
    default:  return TF_ERR;
  }

  ctxStackPush(ctx,createIntObject(result));
  return TF_OK;
}
/*==================== Main =========================*/

int main(int argc,char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  /* Read the program in memory for parsing */

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    perror("Opening  Toy Forth program.");
    return 1;
  }
  fseek(fp, 0, SEEK_END);
  long file_size = ftell(fp);
  printf("File Size: %ld\n", file_size);
  
  fseek(fp, 0, SEEK_SET);
  char* prgtext = xmalloc(file_size+1);
  fread(prgtext, file_size, 1, fp);
  prgtext[file_size] = 0;
  fclose(fp);

  tfobj *prg = compile(prgtext);
  print_object(prg);
  tfctx *ctx = create_context();
  exec(ctx, prg);
  printf("Stack content at end: ");
  print_object(ctx->stack);
  return 0;
}
