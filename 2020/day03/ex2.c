#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entry_t {
  char *value;
  struct entry_t *next;
} entry_t;

size_t compute_nb_trees(char **array, size_t max_x, size_t max_y, size_t dx, size_t dy) {
  size_t nb_trees = 0;
  size_t x = 0, y = 0;

  while (y < max_y - dy) {
    y += dy;
    x = (x + dx) % max_x;
    if (array[y][x] == '#') {
      nb_trees++;
    }
  }

  return nb_trees;
}


int main() {
  char buffer[64], **array;
  entry_t *entries, *entry;
  entry_t **entry_ptr;
  size_t max_x, max_y, y;

  entry_ptr = &entries;
  entries = NULL;
  max_y = 0;
  while(fgets(buffer, sizeof(buffer), stdin)) {
    max_x = strlen(buffer) - 1; /* fgets keeps \n */

    *entry_ptr = (entry_t *)malloc(sizeof(entry_t));
    (*entry_ptr)->value = (char *)malloc(max_x);
    strncpy((*entry_ptr)->value, buffer, max_x);
    (*entry_ptr)->next = NULL;

    max_y++;
    entry_ptr = &((*entry_ptr)->next);
  }

  array = malloc(max_y * sizeof(char *));
  entry = entries;
  for (y = 0; entry; entry = entry->next, y++) {
    array[y] = entry->value;
  }

  printf("%ld\n", compute_nb_trees(array, max_x, max_y, 1, 1)
               * compute_nb_trees(array, max_x, max_y, 3, 1)
               * compute_nb_trees(array, max_x, max_y, 5, 1)
               * compute_nb_trees(array, max_x, max_y, 7, 1)
               * compute_nb_trees(array, max_x, max_y, 1, 2));

  free(array);
  while (entries != NULL) {
    entry_t *next_entry = entries->next;
    free(entries->value);
    free(entries);
    entries = next_entry;
  }

  return 0;
}
