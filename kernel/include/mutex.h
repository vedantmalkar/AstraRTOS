#ifndef H_MUTEX
#define H_MUTEX
#include "stdint.h"

typedef struct{
    int is_locked;
    int task_num_owner;
    int recursive_depth;
} os_mutex_t;

void os_mutex_init(os_mutex_t *mutex);
void os_mutex_take(os_mutex_t *mutex);
void os_mutex_give(os_mutex_t *mutex);

#endif