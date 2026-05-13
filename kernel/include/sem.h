#ifndef H_SEM
#define H_SEM

typedef struct semaphore
{
    int count;
    int max_count;
}os_sem_t;


void os_sem_init(os_sem_t *sem, int initial_count, int max_count);
void os_sem_take(os_sem_t *sem);
void os_sem_give(os_sem_t *sem);

#endif
