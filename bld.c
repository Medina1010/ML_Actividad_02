#include <stdlib.h>

#define BLD_IMPLEMENTATION
#define CLIBS " -lm"
#include "bld.h"

int main(int argc, char **argv) {
  rebuild(argc, argv);
  std_compile("src/main");
  cmd("src/main");
  return 0;
}
