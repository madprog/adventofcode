#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char c, pos1_ok, pos2_ok, *idx, *password;
    long pos1, pos2;
    size_t pw_len;

    idx = buffer;
    pos1 = strtol(idx, &idx, 10) - 1;
    assert(buffer, *(idx++), '-');
    pos2 = strtol(idx, &idx, 10) - 1;
    assert(buffer, *(idx++), ' ');
    c = *(idx++);
    assert(buffer, *(idx++), ':');
    assert(buffer, *(idx++), ' ');
    password = idx;
    pw_len = strlen(password);

    pos1_ok = pos1 < pw_len && password[pos1] == c;
    pos2_ok = pos2 < pw_len && password[pos2] == c;

    if (pos1_ok ^ pos2_ok) {
      nb_good++;
    }
  }

  printf("%ld\n", nb_good);

  return 0;
}
