#include "sem.h"
#include "task.h"
#define ICSR (*((volatile uint32_t *)0xE000ED04))
extern os_tcb_t os_tasks[];
extern os_tcb_t *os_current_task_ptr;
extern uint32_t os_get_task_count();

void os_sem_init(os_sem_t *sem, int initial_count, int max_count){
    sem->count = initial_count;
    sem->max_count = max_count;
}

void os_sem_take(os_sem_t *sem){
    while(1){
        __asm volatile ("cpsid i");
        if(sem->count > 0){
            sem->count--;
            __asm volatile ("cpsie i");
            break;
        }
        else{
            os_current_task_ptr->state = TASK_SEM_WAITING;
            os_current_task_ptr->waiting_for_resource = sem;
            __asm volatile ("cpsie i");
            ICSR |= (1 << 28);
        }


    }
}

void os_sem_give(os_sem_t *sem){
    __asm volatile ("cpsid i");
    if(sem->count < sem->max_count){
        sem->count++;
    }
    uint32_t best_priority  = 0;
    int chosen_index = -1;
    for(uint32_t i =0; i < os_get_task_count(); i++){
        if(os_tasks[i].state == TASK_SEM_WAITING && os_tasks[i].waiting_for_resource == sem){
            if(chosen_index == -1 || (os_tasks[i].priority > best_priority)){
                best_priority = os_tasks[i].priority;
                chosen_index = i;
            }
        }
    }
    if(chosen_index != -1){
        os_tasks[chosen_index].state = TASK_READY;
        os_tasks[chosen_index].waiting_for_resource = 0;
    }    
    __asm volatile ("cpsie i");
}
