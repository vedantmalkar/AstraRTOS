#include "gpio.h"

void gpio_set_mode(uint32_t base, uint32_t pin, uint32_t mode){
    int pin_offset = pin*2;
    GPIO_MODER(base) &= ~(3 << pin_offset);
    GPIO_MODER(base) |= (mode << pin_offset);
}

void gpio_toggle(uint32_t base, uint32_t pin){
    GPIO_ODR(base) ^= (1 << pin); 

}

void gpio_write(uint32_t base, uint32_t pin, uint32_t value){
    if(value == 1){
        GPIO_BSRR(base) = (1 << pin);   // set
    }else{
        GPIO_BSRR(base) = (1 << (pin + 16));    // reset    
    }
}

uint32_t gpio_read(uint32_t base, uint32_t pin){    
    return ((GPIO_IDR(base)) >> pin) & 1;
}