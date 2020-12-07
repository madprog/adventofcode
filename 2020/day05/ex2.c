#include <stdio.h>
#include <strings.h>

int main() {
  char buffer[64];
  char found_seats[128];
  int i;

  bzero(found_seats, sizeof(found_seats));

  while (fgets(buffer, sizeof(buffer), stdin)) {
    char *c;
    int min_row = 0;
    int max_row = 127;
    int min_col = 0;
    int max_col = 7;

    for (c = buffer; *c && *c != '\n'; c++) {
      switch (*c) {
        case 'F':
            max_row = min_row + ((max_row - min_row) >> 1);
            break;
        case 'B':
            min_row = min_row + ((max_row - min_row + 1) >> 1);
            break;
        case 'L':
            max_col = min_col + ((max_col - min_col) >> 1);
            break;
        case 'R':
            min_col = min_col + ((max_col - min_col + 1) >> 1);
            break;
      }
    }

    found_seats[min_row] |= 1 << min_col;
  }

  for (i = 1; i < 1023; i++) {
    if (    (found_seats[(i - 1) >> 3] & (1 << ((i - 1) & 0x7)))
        && !(found_seats[(i + 0) >> 3] & (1 << ((i + 0) & 0x7)))
        &&  (found_seats[(i + 1) >> 3] & (1 << ((i + 1) & 0x7)))) {
      printf("%d\n", i);
    }
  }

  return 0;
}
