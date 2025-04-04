#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
  char *str = NULL;
  size_t len = 0;
  ssize_t read;
  printf("hello\n");
  read = getline(&str, &len, stdin);
  if (read != -1) {
    printf("%s\n", str);
  }
  int foo = 1;

  return 0;
}
