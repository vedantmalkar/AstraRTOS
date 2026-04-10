#include "rcc.h"

#define RCC_BASE 0x40023800

#define RCC_AHB1ENR (*(volatile uint32_t*)(RCC_BASE + 0x30))    //For GPIOA-GPIOI, DMA1,2
#define RCC_AHB2ENR (*(volatile uint32_t*)(RCC_BASE + 0x34))    //For USB, RNG
#define RCC_AHB3ENR (*(volatile uint32_t*)(RCC_BASE + 0x38))    //External Memory (FSMC/FMC)
#define RCC_APB1ENR (*(volatile uint32_t*)(RCC_BASE + 0x40))    //For UART2,3 , I2C
#define RCC_APB2ENR (*(volatile uint32_t*)(RCC_BASE + 0x44))    //For UART1, ADC, SPI1
#define RCC_CSR (*(volatile uint32_t*)(RCC_BASE + 0x74))    //Reset Flags and LSI Enable

void rcc_enable_gpio(uint8_t port){
    RCC_AHB1ENR |= (1 << port);
}