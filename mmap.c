#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h> // memory management

int main(void) {
  int fd = open("mmap.c", O_RDONLY);
  printf("Open file descriptor: %d\n", fd);
  // da capire cosa fa davvero nel manuale 2
  void *mem = mmap(NULL, 100, PROT_READ, MAP_FILE|MAP_SHARED, fd, 0);
  printf("File mapped at %p\n", mem);
  char *s = mem;
  for (int j = 0; j < 10; j++) {
    printf("s[%d] = %c\n", j, s[j]);
  }
  return 0;
}
