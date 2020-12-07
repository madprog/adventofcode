#include <stdio.h>
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
  char buffer[512];
  unsigned char passport_keys;

  while(!feof(stdin)) {
    passport_keys = 0;

    while (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') {
      size_t buffer_len = strlen(buffer) - 1;
      size_t idx = 0;

      while (idx < buffer_len) {
        if (strncmp(buffer + idx, "byr:", 4) == 0) {
          passport_keys |= 1 << BYR;
        } else if (strncmp(buffer + idx, "iyr:", 4) == 0) {
          passport_keys |= 1 << IYR;
        } else if (strncmp(buffer + idx, "eyr:", 4) == 0) {
          passport_keys |= 1 << EYR;
        } else if (strncmp(buffer + idx, "hgt:", 4) == 0) {
          passport_keys |= 1 << HGT;
        } else if (strncmp(buffer + idx, "hcl:", 4) == 0) {
          passport_keys |= 1 << HCL;
        } else if (strncmp(buffer + idx, "ecl:", 4) == 0) {
          passport_keys |= 1 << ECL;
        } else if (strncmp(buffer + idx, "pid:", 4) == 0) {
          passport_keys |= 1 << PID;
        } else if (strncmp(buffer + idx, "cid:", 4) == 0) {
          passport_keys |= 1 << CID;
        }

        for (idx += 4; idx < buffer_len && buffer[idx] != ' '; idx++);
        idx++;
      }
    }

    if ((passport_keys & 0x7f) == 0x7f) {
      nb_valid++;
    }
  }

  printf("%ld\n", nb_valid);

  return 0;
}
