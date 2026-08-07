#include "gpio.h"
#include "rcc.h"

void gpio_set_mode(uint32_t base, uint32_t pin, uint32_t mode) {
    int pin_offset = pin * 2;
    GPIO_MODER(base) &= ~(3 << pin_offset);
    GPIO_MODER(base) |= (mode << pin_offset);
}

void gpio_toggle(uint32_t base, uint32_t pin) {
    GPIO_ODR(base) ^= (1 << pin);
}

void gpio_write(uint32_t base, uint32_t pin, uint32_t value) {
    if(value == 1) {
        GPIO_BSRR(base) = (1 << pin); // set
    }
    else {
        GPIO_BSRR(base) = (1 << (pin + 16)); // reset
    }
}

uint32_t gpio_read(uint32_t base, uint32_t pin) {
    return ((GPIO_IDR(base)) >> pin) & 1;
}

void gpio_set_otype(uint32_t base, uint32_t pin, uint32_t o_type) {
    GPIO_OTYPER(base) &= ~(1 << pin);
    GPIO_OTYPER(base) |= (o_type << pin);
}

void gpio_set_ospeed(uint32_t base, uint32_t pin, uint32_t o_speed) {
    uint32_t shift = 2 * pin;
    GPIO_OSPEEDR(base) &= ~(3 << shift);
    GPIO_OSPEEDR(base) |= (o_speed << shift);
}

void gpio_set_pull(uint32_t base, uint32_t pin, uint32_t pull) {
    uint32_t shift = 2 * pin;
    GPIO_PUPDR(base) &= ~(3 << shift);
    GPIO_PUPDR(base) |= (pull << shift);
}

void gpio_set_af(uint32_t base, uint32_t pin, uint32_t af) {
    if(pin < 8) {
        uint32_t shift = 4 * pin;
        GPIO_AFRL(base) &= ~(0x0F << shift);
        GPIO_AFRL(base) |= (af << shift);
    }
    else {
        uint32_t shift = (pin - 8) * 4;
        GPIO_AFRH(base) &= ~(0x0F << shift);
        GPIO_AFRH(base) |= (af << shift);
    }
}

/* struct created and given as input here */
void gpio_init(uint32_t base, uint32_t pin, gpio_config_t *config) {
    uint32_t gpio_enable = (base - GPIOA_BASE) / 0x400;

    rcc_enable_gpio(gpio_enable);
    gpio_set_mode(base, pin, config->mode);
    gpio_set_otype(base, pin, config->otype);
    gpio_set_ospeed(base, pin, config->ospeed);
    gpio_set_pull(base, pin, config->pull);

    if(config->mode == GPIO_MODE_AF) {
        gpio_set_af(base, pin, config->af);
    }
}