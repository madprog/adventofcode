#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct group_t {
  char answers[26];
  struct group_t *next;
} group_t;

int main() {
  char buffer[32], *i, is_first;
  struct group_t *groups = NULL, *ptr, **pptr;
  int total_nb_answers;

  ptr = NULL;
  pptr = &groups;
  while (fgets(buffer, sizeof(buffer), stdin)) {
    if (ptr == NULL || buffer[0] == '\n' || buffer[0] == '\0') {
      ptr = *pptr = malloc(sizeof(*groups));
      bzero(ptr->answers, sizeof(ptr->answers));
      ptr->next = NULL;
      pptr = &ptr->next;
      is_first = 1;
    }

    if (buffer[0] != '\n' && buffer[0] != '\0') {
      if (is_first) {
        is_first = 0;
        for (i = buffer; *i != '\n' && *i != '\0'; i++) {
          if ('a' <= *i && *i <= 'z') {
            ptr->answers[*i - 'a'] = 1;
          }
        }
      } else {
        for (i = buffer; *i != '\n' && *i != '\0'; i++) {
          if ('a' <= *i && *i <= 'z') {
            ptr->answers[*i - 'a'] += 1;
          }
        }

        for (i = ptr->answers; i - ptr->answers < sizeof(ptr->answers); i++) {
          if (*i) {
            (*i)--;
          }
        }
      }
    }
  }

  total_nb_answers = 0;
  for (ptr = groups; ptr; ptr = ptr->next) {
    int nb_answers = 0;
    for (i = ptr->answers; i - ptr->answers < sizeof(ptr->answers); i++) {
      if (*i) {
        nb_answers++;
      }
    }
    total_nb_answers += nb_answers;
  }

  printf("%d\n", total_nb_answers);

  for (ptr = groups; ptr;) {
    group_t *next_ptr = ptr->next;
    free(ptr);
    ptr = next_ptr;
  }

  return 0;
}
