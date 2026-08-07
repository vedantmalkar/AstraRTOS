#ifndef RCC_H
#define RCC_H

#include <stdint.h>

/* EN defines prefered not be used in
 * kernel, needs updating in uart rn
 */

#define GPIOA_EN 0
#define GPIOB_EN 1
#define GPIOC_EN 2
#define GPIOD_EN 3
#define GPIOE_EN 4
#define GPIOF_EN 5
#define GPIOG_EN 6
#define GPIOH_EN 7
#define GPIOI_EN 8
#define GPIOJ_EN 9
#define GPIOK_EN 10

#define USART1_EN 1
#define USART2_EN 2
#define USART3_EN 3

void rcc_enable_gpio(uint8_t port);
void rcc_disable_gpio(uint8_t port);
void rcc_enable_uart(uint8_t uart);
void rcc_disable_uart(uint8_t uart);

#endif