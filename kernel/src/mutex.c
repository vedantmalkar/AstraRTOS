#include "mutex.h"
#include "task.h"
#define ICSR (*((volatile uint32_t *)0xE000ED04))
extern os_tcb_t os_tasks[];
extern os_tcb_t *os_current_task_ptr;
extern uint32_t os_get_task_count();

void os_mutex_init(os_mutex_t *mutex){
    mutex->is_locked = 0;
    mutex->task_num_owner = -1;
    mutex->recursive_depth = 0;
}
void os_mutex_take(os_mutex_t *mutex){
    while(1){
        __asm volatile ("cpsid i");
        if(mutex->is_locked == 0){
            mutex->is_locked = 1;
            mutex->task_num_owner = os_current_task_ptr->task_num;
            mutex->recursive_depth = 1;
            __asm volatile ("cpsie i");
            break;
        }
        else if(mutex->is_locked == 1 && mutex->task_num_owner == os_current_task_ptr->task_num){
            mutex->recursive_depth ++;
            __asm volatile ("cpsie i");
            break;
        }
        else{
            os_tcb_t *owner = &os_tasks[mutex->task_num_owner];
            if(os_current_task_ptr->priority > owner->priority){
                owner->priority = os_current_task_ptr->priority; 
            }
            os_current_task_ptr->state = TASK_MUTEX_WAITING;
            os_current_task_ptr->waiting_for_resource = (void *)mutex;
            __asm volatile ("cpsie i");
            ICSR |= (1 << 28);
        }
    }
}
void os_mutex_give(os_mutex_t *mutex){
    __asm volatile ("cpsid i");
    if(mutex->task_num_owner == os_current_task_ptr->task_num){
        mutex->recursive_depth --;
        if(mutex->recursive_depth > 0){
            __asm volatile ("cpsie i");
            return;
        }
        mutex->is_locked = 0;
        mutex->task_num_owner = -1;
        os_current_task_ptr->priority = os_current_task_ptr->base_priority;
        uint32_t best_priority  = 0;
        int chosen_index = -1;
        for(uint32_t i = 0; i < os_get_task_count() ; i++){
            if(os_tasks[i].state == TASK_MUTEX_WAITING){
                if(os_tasks[i].waiting_for_resource == (void *)mutex){
                    if(chosen_index == -1 || (os_tasks[i].priority > best_priority)){
                        best_priority = os_tasks[i].priority;
                        chosen_index = i;
                    }
                }
            }
        }
        if(chosen_index != -1){
            os_tasks[chosen_index].state = TASK_READY;
            os_tasks[chosen_index].waiting_for_resource = 0;
        }
    }
    __asm volatile ("cpsie i");
}