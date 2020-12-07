#include <stdio.h>

int main() {
  char buffer[64];
  int max_seat_id = 0;

  while (fgets(buffer, sizeof(buffer), stdin)) {
    char *c;
    int seat_id;
    int min_row = 0;
    int max_row = 127;
    int min_col = 0;
    int max_col = 7;

    for (c = buffer; *c && *c != '\n'; c++) {
      switch (*c) {
        case 'F':
            max_row = (int)(min_row + (max_row - min_row) / 2);
            break;
        case 'B':
            min_row = (int)(min_row + (max_row - min_row + 1) / 2);
            break;
        case 'L':
            max_col = (int)(min_col + (max_col - min_col) / 2);
            break;
        case 'R':
            min_col = (int)(min_col + (max_col - min_col + 1) / 2);
            break;
      }
    }

    seat_id = (min_row << 3) | min_col;
    if (seat_id > max_seat_id) {
      max_seat_id = seat_id;
    }
  }

  printf("%d\n", max_seat_id);

  return 0;
}
