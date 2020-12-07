#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entry_t {
  char *value;
  struct entry_t *next;
} entry_t;

int main() {
  char buffer[64], **array;
  entry_t *entries, *entry;
  entry_t **entry_ptr;
  size_t max_x, max_y, nb_trees, x, y;

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

  nb_trees = 0;
  for (y = 0; y < max_y; y++) {
    x = (3 * y) % max_x;
    if (array[y][x] == '#') {
      nb_trees++;
    }
  }

  printf("%ld\n", nb_trees);

  free(array);
  while (entries != NULL) {
    entry_t *next_entry = entries->next;
    free(entries->value);
    free(entries);
    entries = next_entry;
  }

  return 0;
}
