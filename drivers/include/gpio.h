#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define GPIOA_BASE 0x40020000
#define GPIOB_BASE 0x40020400
#define GPIOC_BASE 0x40020800
#define GPIOD_BASE 0x40020C00
#define GPIOE_BASE 0x40021000
#define GPIOF_BASE 0x40021400
#define GPIOG_BASE 0x40021800
#define GPIOH_BASE 0x40021C00

#define GPIO_MODER(base) (*(volatile uint32_t*)((base) + 0x00))
#define GPIO_IDR(base) (*(volatile uint32_t*)((base) + 0x10))
#define GPIO_ODR(base) (*(volatile uint32_t*)((base) + 0x14))
#define GPIO_BSRR(base) (*(volatile uint32_t*)((base) + 0x18))
#define GPIO_AFRL(base) (*(volatile uint32_t*)((base) + 0x20))

#define GPIO_MODE_INPUT 0
#define GPIO_MODE_OUTPUT 1
#define GPIO_MODE_AF 2
#define GPIO_MODE_ANALOG 3

void gpio_set_mode(uint32_t base, uint32_t pin, uint32_t mode);
void gpio_toggle(uint32_t base, uint32_t pin);
void gpio_write(uint32_t base, uint32_t pin, uint32_t value);
uint32_t gpio_read(uint32_t base, uint32_t pin);

#endif