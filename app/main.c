// AstraRTOS - main kernel

#include "timer.h"
#include "task.h"

void app_timer_demo_start(void);

void main(void){
    app_timer_demo_start();
    os_start();
    while(1){
        }
}