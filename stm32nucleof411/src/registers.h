#ifndef REGISTER_H
#define REGISTER_H

typedef unsigned long register_value_t;
typedef volatile unsigned long* register_t;

#define PERIPHERAL_BASE (register_t)0x4000000
#define GPIO_BASE (register_t)0x40020000
#define RCC_BASE (register_t)(0x40023800)
#define RCC_AHB1_ENABLE_BASE (RCC_BASE + 0x30)
#define RCC_AHB1_GPIOAEN_BIT 0

register_value_t load_register(register_t reg);
void store_register(register_t reg, register_value_t value);
void set_bit_high(register_t reg, int bit);

#endif
