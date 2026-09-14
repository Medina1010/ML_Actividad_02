#include <stdlib.h>

#define BLD_IMPLEMENTATION
#define CLIBS " -lm"
#include "bld.h"

int main(int argc, char **argv) {
  rebuild(argc, argv);
  cmd("gcc -o src/main src/main.c -lm -O3 -ffast-math");
  cmd("src/main");
  return 0;
}
