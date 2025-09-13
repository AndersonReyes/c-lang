
#include "registers.h"
#include "stdio.h"


int main() {
  int test = 0;
  register_t demo_register = (register_t)(&test);
  register_value_t before = load_register(demo_register);
  set_bit_high(demo_register, 2);

  register_value_t after = load_register(demo_register);

  printf("Value at register %p: before=%lx, after=%lx \n", demo_register, before, after);

  return 0;
}
