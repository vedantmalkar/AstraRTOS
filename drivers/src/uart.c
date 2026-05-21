#include "uart.h"
#include "rcc.h"
#include "gpio.h"
#include "system_init.h"

#define RINGBUFFER_SIZE 128
typedef struct{
    char buffer[RINGBUFFER_SIZE];
    volatile uint32_t head;
    volatile uint32_t tail;
} uart_ringbuffer_t;
static uart_ringbuffer_t ring_buffer = {.head = 0 , .tail = 0};

//Starts only UART2
void uart_init(void){
    rcc_enable_gpio(GPIOA_EN);
    rcc_enable_uart(USART2_EN);

    GPIO_MODER(GPIOA_BASE) &= ~((3 << (2*2)) | (3 << (3*2))); //Clear Pins 2 and 3
    GPIO_MODER(GPIOA_BASE) |= ((2 << (2*2)) | (2 << (3*2))); //Sets to AF mode

    GPIO_AFRL(GPIOA_BASE) &= ~((0xF << (2*4)) | (0xF << (3*4))); //Clear 
    GPIO_AFRL(GPIOA_BASE) |= ((7 << (2*4)) | (7 << (3*4))); //Selecting AF to USART2

    USART2_BRR = 0x1250; //9600 BaudRate (Condition: Peripheral Clock (APB1) = 45MHz)

    //8N1
    USART2_CR1 &= ~(1 << 12);
    USART2_CR2 &= ~(3 << 12);
    USART2_CR1 &= ~(1 << 10);

    //USART Enable, TX Enable, RX Enable
    USART2_CR1 |= (1 << 13) | (1 << 3) | (1 << 2);

    //RXNEIE Enalbe
    USART2_CR1 |= (1 << 5);

    //NVIC-IRQ 
    NVIC_ISER1 |= (1 << 6);
}

void uart_send_char(char c){
    while(!(USART2_SR & (1 << 7)));//Checking bit 7 of SR
    USART2_DR = (uint8_t)c; //Write to DR
}

//After writing to DR the TXE flag (bit 7) resets back

void uart_send_string(char *str){
    while(*str){
        uart_send_char(*str++);
    }
}

int uart_receive_char_polling(void){
    USART2_CR1 &= ~(1 << 5);

    uint32_t initial_ticks = system_ticks;

    while(!(USART2_SR & (1 << 5))){ //Checking bit 5 of SR
        if(system_ticks - initial_ticks >= TIMEOUT){
            return -1; //Timeout if nothing is received (after 1 sec)
        }
    }
    int data = (int)(USART2_DR & 0xFF);
    USART2_CR1 |= (1 << 5);

    return data;
}

void uart_receive_string_polling(char *buffer, int max_length){
    int i = 0;
    int c;

    while(i < max_length - 1){ //Iterate until (max - 1)
        c = uart_receive_char_polling(); //Receive characters

        if(c == -1) break; //Break if timeout
        if(c == '\r' || c == '\n') break; //Break if carriage return or newline

        buffer[i++] = (char)c; //Put in buffer
    }

    buffer[i] = '\0'; //Null terminator
}

int uart_receive_byte(char *byte){
    if(ring_buffer.head == ring_buffer.tail){
        return 0;
    }
    *byte = ring_buffer.buffer[ring_buffer.tail];
    ring_buffer.tail = (ring_buffer.tail+1)%RINGBUFFER_SIZE;

    return 1;
}

void USART2_IRQHandler(void){
    if(USART2_SR & (1 << 5)){
        char recd_byte = (char)USART2_DR;
        uint32_t next_head = (ring_buffer.head+1)%RINGBUFFER_SIZE;
        if(next_head != ring_buffer.tail){
            ring_buffer.buffer[ring_buffer.head] = recd_byte;
            ring_buffer.head = next_head;

            ICSR |= (1 << 28);
        }
    }
}