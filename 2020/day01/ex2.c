#include <stdio.h>
#include <stdlib.h>

typedef struct entry_t {
  int value;
  struct entry_t *next;
} entry_t;

int main() {
  char buffer[64];
  entry_t *entries = NULL;
  entry_t **entry_ptr;
  entry_t *i, *j, *k;

  entry_ptr = &entries;
  while(fgets(buffer, sizeof(buffer), stdin)) {
    *entry_ptr = (entry_t *)malloc(sizeof(entry_t));
    (*entry_ptr)->value = strtol(buffer, NULL, 10);
    (*entry_ptr)->next = NULL;
    entry_ptr = &((*entry_ptr)->next);
  }

  for (i = entries; i != NULL; i = i->next) {
    for (j = i->next; j != NULL; j = j->next) {
      for (k = j->next; k != NULL; k = k->next) {
        if (i->value + j->value + k->value == 2020) {
          printf("%d\n", i->value * j->value * k->value);
        }
      }
    }
  }

  i = entries;
  while (i != NULL) {
    entry_t *next_i = i->next;
    free(i);
    i = next_i;
  }

  return 0;
}
