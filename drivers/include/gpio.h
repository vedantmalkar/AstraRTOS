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

#define GPIO_MODER(base) (*(volatile uint32_t *)((base) + 0x00))
#define GPIO_OTYPER(base) (*(volatile uint32_t *)((base) + 0x04))
#define GPIO_OSPEEDR(base) (*(volatile uint32_t *)((base) + 0x08))
#define GPIO_PUPDR(base) (*(volatile uint32_t *)((base) + 0x0C))
#define GPIO_IDR(base) (*(volatile uint32_t *)((base) + 0x10))
#define GPIO_ODR(base) (*(volatile uint32_t *)((base) + 0x14))
#define GPIO_BSRR(base) (*(volatile uint32_t *)((base) + 0x18))
#define GPIO_AFRL(base) (*(volatile uint32_t *)((base) + 0x20))
#define GPIO_AFRH(base) (*(volatile uint32_t *)((base) + 0x24))

#define GPIO_MODE_INPUT 0
#define GPIO_MODE_OUTPUT 1
#define GPIO_MODE_AF 2
#define GPIO_MODE_ANALOG 3

#define GPIO_OTYPE_PP 0
#define GPIO_OTYPE_OD 1

#define GPIO_OSPEED_LOW 0
#define GPIO_OSPEED_MEDIUM 1
#define GPIO_OSPEED_HIGH 2
#define GPIO_OSPEED_V_HIGH 3

#define GPIO_PULL_NONE 0
#define GPIO_PULL_UP 1
#define GPIO_PULL_DOWN 2
#define GPIO_PULL_RESERVED 3

typedef struct gpio_config_t {
    uint8_t mode;
    uint8_t otype;
    uint8_t ospeed;
    uint8_t pull;
    uint8_t af;
} gpio_config_t;

void gpio_set_mode(uint32_t base, uint32_t pin, uint32_t mode);
void gpio_toggle(uint32_t base, uint32_t pin);
void gpio_write(uint32_t base, uint32_t pin, uint32_t value);
uint32_t gpio_read(uint32_t base, uint32_t pin);
void gpio_set_otype(uint32_t base, uint32_t pin, uint32_t o_type);
void gpio_set_ospeed(uint32_t base, uint32_t pin, uint32_t o_speed);
void gpio_set_pull(uint32_t base, uint32_t pin, uint32_t pull);
void gpio_set_af(uint32_t base, uint32_t pin, uint32_t af);
void gpio_init(uint32_t base, uint32_t pin, gpio_config_t *config);

#endif