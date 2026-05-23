#ifndef H_TIMER
#define H_TIMER

#include <stdint.h>

#define OS_MAX_TIMERS 10

typedef void (*os_timer_callback_t)(void);

typedef enum {
    TIMER_STOPPED,
    TIMER_RUNNING,
    TIMER_EXPIRED
} os_timer_state_t;

typedef struct {
    uint32_t period_ticks;       
    uint32_t remaining_ticks;    
    os_timer_callback_t callback;
    uint8_t repeating;           
    os_timer_state_t state;
} os_timer_t;

void os_timer_init(os_timer_t *timer, uint32_t period_ticks, uint8_t repeating, os_timer_callback_t callback);
void os_timer_start(os_timer_t *timer);
void os_timer_stop(os_timer_t *timer);
void os_timer_reset(os_timer_t *timer);
void os_timer_tick(void);   

#endif
