#include <stdio.h>
#include <stdarg.h>

void foo(char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  char *p = fmt;
  while  (*p) {
    if (*p == 'i') {
      int i = va_arg(ap, int);
      printf("%d\n", i);
    } else if (*p == 's') {
      char *s = va_arg(ap, char*);
      printf("%s\n", s);
    } else {
      printf("Wrong specifier\n");
      goto cleanup;
    }
    p++;
  }
cleanup:
  va_end(ap);
}


int main(void) {
  
  printf("Hello World!\n");
  foo("iisi", 10, 20, "ciao miao", 5);
  return 0;
}
