#include <stdio.h>
#include <stdlib.h>

typedef struct entry_t {
  long value;
  struct entry_t *next;
} entry_t;

int main() {
  char buffer[64];
  entry_t *entries = NULL;
  entry_t **entry_ptr;
  entry_t *i, *j;

  entry_ptr = &entries;
  while(fgets(buffer, sizeof(buffer), stdin)) {
    *entry_ptr = (entry_t *)malloc(sizeof(entry_t));
    (*entry_ptr)->value = strtol(buffer, NULL, 10);
    (*entry_ptr)->next = NULL;
    entry_ptr = &((*entry_ptr)->next);
  }

  for (i = entries; i != NULL; i = i->next) {
    for (j = i->next; j != NULL; j = j->next) {
      if (i->value + j->value == 2020) {
        printf("%ld\n", i->value * j->value);
      }
    }
  }

  while (entries != NULL) {
    entry_t *next_entry = entries->next;
    free(entries);
    entries = next_entry;
  }

  return 0;
}
