#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BYR = 0;
const int IYR = 1;
const int EYR = 2;
const int HGT = 3;
const int HCL = 4;
const int ECL = 5;
const int PID = 6;
const int CID = 7;

int main() {
  size_t nb_valid = 0;
  size_t i = 0;
  char buffer[512];
  unsigned char passport_keys;

  while(!feof(stdin)) {
    passport_keys = 0;

    while (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') {
      size_t buffer_len = strlen(buffer) - 1;
      size_t idx = 0;

      while (idx < buffer_len) {
        if (strncmp(buffer + idx, "byr:", 4) == 0) {
          char *ptr;
          long byr = strtol(buffer + idx + 4, &ptr, 10);
          if (1920 <= byr && byr <= 2002) {
            passport_keys |= 1 << BYR;
          }
        } else if (strncmp(buffer + idx, "iyr:", 4) == 0) {
          char *ptr;
          long iyr = strtol(buffer + idx + 4, &ptr, 10);
          if (2010 <= iyr && iyr <= 2020) {
            passport_keys |= 1 << IYR;
          }
        } else if (strncmp(buffer + idx, "eyr:", 4) == 0) {
          char *ptr;
          long eyr = strtol(buffer + idx + 4, &ptr, 10);
          if (2020 <= eyr && eyr <= 2030) {
            passport_keys |= 1 << EYR;
          }
        } else if (strncmp(buffer + idx, "hgt:", 4) == 0) {
          char *ptr;
          long hgt = strtol(buffer + idx + 4, &ptr, 10);
          if (   (strncmp(ptr, "cm", 2) == 0 && 150 <= hgt && hgt <= 193)
              || (strncmp(ptr, "in", 2) == 0 && 59 <= hgt && hgt <= 76)) {
            passport_keys |= 1 << HGT;
          }
        } else if (strncmp(buffer + idx, "hcl:", 4) == 0) {
          char *ptr;
          /*long hcl =*/ strtol(buffer + idx + 5, &ptr, 16);
          if (buffer[idx + 4] == '#' && ptr - buffer - idx == 4 + 7) {
            passport_keys |= 1 << HCL;
          }
        } else if (strncmp(buffer + idx, "ecl:", 4) == 0) {
          char after_char = buffer[idx + 7];
          if (   (after_char == ' ' || after_char == '\0' || after_char == '\n')
              && (   strncmp(buffer + idx + 4, "amb", 3) == 0
                  || strncmp(buffer + idx + 4, "blu", 3) == 0
                  || strncmp(buffer + idx + 4, "brn", 3) == 0
                  || strncmp(buffer + idx + 4, "gry", 3) == 0
                  || strncmp(buffer + idx + 4, "grn", 3) == 0
                  || strncmp(buffer + idx + 4, "hzl", 3) == 0
                  || strncmp(buffer + idx + 4, "oth", 3) == 0)) {
            passport_keys |= 1 << ECL;
          }
        } else if (strncmp(buffer + idx, "pid:", 4) == 0) {
          char *ptr;
          /*long pid =*/ strtol(buffer + idx + 4, &ptr, 10);
          if (ptr - buffer - idx == 9 + 4) {
            passport_keys |= 1 << PID;
          }
        } else if (strncmp(buffer + idx, "cid:", 4) == 0) {
          passport_keys |= 1 << CID;
        }

        while (idx < buffer_len && buffer[idx] != ' ') idx++;
        idx++;
      }
    }

    if ((passport_keys & 0x7f) == 0x7f) {
      nb_valid++;
    }
    i++;
  }

  printf("%ld\n", nb_valid);

  return 0;
}
