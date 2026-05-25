#ifndef UART_H
#define UART_H

#include <stdint.h>

#define USART2_BASE 0x40004400
#define USART2_SR (*(volatile uint32_t*)(USART2_BASE + 0x00))
#define USART2_DR (*(volatile uint32_t*)(USART2_BASE + 0x04))
#define USART2_BRR (*(volatile uint32_t*)(USART2_BASE + 0x08))
#define USART2_CR1 (*(volatile uint32_t*)(USART2_BASE + 0x0C))
#define USART2_CR2 (*(volatile uint32_t*)(USART2_BASE + 0x10))
#define NVIC_ISER1 (*(volatile uint32_t*)(0xE000E104))
#define ICSR (*((volatile uint32_t *)0xE000ED04))

#define TIMEOUT 1000

void uart_init(void);
void uart_send_char(char c);
void uart_send_string(char *str);
int uart_receive_char_polling(void);
void uart_receive_string_polling(char *buffer, int max_length);
int uart_receive_byte(char *byte);

#endif