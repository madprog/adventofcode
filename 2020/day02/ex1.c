#include <stdio.h>
#include <stdlib.h>

void assert(const char *buffer, char val, char expected) {
  if (val != expected) {
    fprintf(stderr, "Invalid format: Expected '%c' and got '%c' in '%s'\n", expected, val, buffer);
    exit(1);
  }
}

int main() {
  char buffer[64];
  size_t nb_good = 0;

  while(fgets(buffer, sizeof(buffer), stdin)) {
    char c, *idx, *password;
    long nb_min, nb_max;
    int i, nb_c;

    idx = buffer;
    nb_min = strtol(idx, &idx, 10);
    assert(buffer, *(idx++), '-');
    nb_max = strtol(idx, &idx, 10);
    assert(buffer, *(idx++), ' ');
    c = *(idx++);
    assert(buffer, *(idx++), ':');
    assert(buffer, *(idx++), ' ');
    password = idx;

    nb_c = 0;
    for (i = 0; password[i]; i++) {
      if (password[i] == c) {
        nb_c++;
      }
    }

    if (nb_min <= nb_c && nb_c <= nb_max) {
      nb_good++;
    }
  }

  printf("%ld\n", nb_good);

  return 0;
}
