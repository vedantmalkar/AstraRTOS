#include "timer.h"

static os_timer_t *os_timers[OS_MAX_TIMERS];
static uint32_t os_timer_count = 0;

void os_timer_init(os_timer_t *timer, uint32_t period_ticks, uint8_t repeating, os_timer_callback_t callback){
    timer->period_ticks    = period_ticks;
    timer->remaining_ticks = period_ticks;
    timer->repeating       = repeating;
    timer->callback        = callback;
    timer->state           = TIMER_STOPPED;
    if(os_timer_count < OS_MAX_TIMERS){
        os_timers[os_timer_count] = timer;
        os_timer_count += 1;
    }
}

void os_timer_start(os_timer_t *timer){
    timer->remaining_ticks = timer->period_ticks;
    timer->state           = TIMER_RUNNING;
}

void os_timer_stop(os_timer_t *timer){
    timer->state = TIMER_STOPPED;
}

void os_timer_reset(os_timer_t *timer){
    timer->remaining_ticks = timer->period_ticks;
    if(timer->state == TIMER_EXPIRED){
        timer->state = TIMER_RUNNING;
    }
}

void os_timer_tick(void){
    for(uint32_t i = 0; i < os_timer_count; i++){
        os_timer_t *t = os_timers[i];
        if(t->state != TIMER_RUNNING){
            continue;
        }
        if(t->remaining_ticks > 0){
            t->remaining_ticks -= 1;
        }
        if(t->remaining_ticks == 0){
            if(t->callback != 0){
                t->callback();
            }
            if(t->repeating == 1){
                t->remaining_ticks = t->period_ticks;
            }
            else{
                t->state = TIMER_EXPIRED;
            }
        }
    }
}
