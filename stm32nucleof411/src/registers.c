#include "registers.h"

register_value_t load_register(register_t reg) { return *reg; }
void store_register(register_t reg, register_value_t value) { *reg = value; }
void set_bit_high(register_t reg, int bit) { (*reg) |= (1 << bit); }

