#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct bag_contents_t {
  int bag_type;
  char bag_name[64];
  int nb_bags;
} bag_contents_t;

#define MAX_BAG_NAMES 1024
#define MAX_BAG_NAME_LENGTH 64
#define MAX_SUB_BAGS_LENGTH 32

static bag_contents_t bag_contents[MAX_BAG_NAMES][MAX_SUB_BAGS_LENGTH];
static char bag_names[MAX_BAG_NAMES][MAX_BAG_NAME_LENGTH];

int bag_name_to_id(const char *bag_name) {
  int bag_id;

  for (bag_id = 0; bag_names[bag_id][0] && bag_id < MAX_BAG_NAMES; bag_id++) {
    if (strcmp(bag_name, bag_names[bag_id]) == 0) {
      return bag_id;
    }
  }

  return -1;
}

char bag_contains(int haystack_bag_id, int needle_bag_id) {
  int sub_bag_id;

  for (sub_bag_id = 0; sub_bag_id < MAX_SUB_BAGS_LENGTH && bag_contents[haystack_bag_id][sub_bag_id].nb_bags > 0; sub_bag_id++) {
    int sub_bag_type = bag_contents[haystack_bag_id][sub_bag_id].bag_type;
    if (sub_bag_type == needle_bag_id || bag_contains(sub_bag_type, needle_bag_id)) {
      return 1;
    }
  }

  return 0;
}

int main() {
  char buffer[128];
  int bag_id, sub_bag_id, i;
  int nb_shiny_gold_bags;
  int shiny_gold_bag_id;

  bzero(bag_names, sizeof(bag_names));
  bzero(bag_contents, sizeof(bag_contents));

  bag_id = 0;
  while (fgets(buffer, sizeof(buffer), stdin)) {
    int k;

    /* copy the bag name to the index */
    for (i = 0; buffer[i] != '\n' && buffer[i] != '\0' && (buffer[i] != ' ' || strncmp(buffer + i, " bags contain ", 13)); i++) {
      bag_names[bag_id][i] = buffer[i];
    }
    bag_names[bag_id][i++] = '\0';

    if (buffer[i] == '\0' || buffer[i] == '\n') {
      printf("Expected 'contain ' at line %d, column %d: %s\n", bag_id + 1, i + 1, buffer);
      exit(1);
    }
    i += 13;

    /* get contents information */
    sub_bag_id = 0;
    if (strcmp(buffer + i, "no other bags.\n") != 0) {
      k = i;
      i = 0;
      while (buffer[k + i] != '\0' && buffer[k + i] != '\n') {
        char *ptr, c;

        bag_contents[bag_id][sub_bag_id].nb_bags = strtol(buffer + k + i, &ptr, 10);
        if (ptr == buffer + k + i) {
          printf("Expected a number at line %d, column %d: %s\n", bag_id + 1, k + i + 1, buffer);
          exit(1);
        }

        ptr++;
        i = ptr - (buffer + k);
        while (buffer[i] && strncmp(buffer + k + i, " bag", 4)) i++;

        c = buffer[k + i];
        buffer[k + i] = '\0';
        strcpy(bag_contents[bag_id][sub_bag_id].bag_name, ptr);
        buffer[k + i] = c;

        i += 4;
        if (buffer[k + i] == 's') i++;
        if (buffer[k + i] == ',' && buffer[k + i + 1] == ' ') i+=2;
        if (buffer[k + i] == '.') i++;

        sub_bag_id++;
      }
    }
    bag_contents[bag_id][sub_bag_id].nb_bags = 0;

    bag_id++;
  }
  bag_names[bag_id][0] = '\0';

  for (bag_id = 0; bag_id < MAX_BAG_NAMES && bag_names[bag_id][0]; bag_id++) {
    for (sub_bag_id = 0; sub_bag_id < MAX_SUB_BAGS_LENGTH && bag_contents[bag_id][sub_bag_id].nb_bags > 0; sub_bag_id++) {
      const char *bag_name;
      int bag_type;

      bag_name = bag_contents[bag_id][sub_bag_id].bag_name;
      bag_type = bag_name_to_id(bag_name);
      if (bag_type < 0) {
        printf("Could not find bag name '%s'\n", bag_name);
        exit(1);
      }
      bag_contents[bag_id][sub_bag_id].bag_type = bag_type;
    }
  }

  nb_shiny_gold_bags = 0;
  shiny_gold_bag_id = bag_name_to_id("shiny gold");
  if (shiny_gold_bag_id < 0) {
    printf("Could not find bag name 'shiny gold'\n");
    exit(1);
  }
  for (bag_id = 0; bag_id < MAX_BAG_NAMES && bag_names[bag_id][0]; bag_id++) {
    if (bag_contains(bag_id, shiny_gold_bag_id)) {
      nb_shiny_gold_bags++;
    }
  }

  printf("%d\n", nb_shiny_gold_bags);

  return 0;
}
