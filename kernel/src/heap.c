#include "heap.h"
#include "mutex.h"

#define SIZE_RAM 100*1024

static uint8_t os_heap[SIZE_RAM];
static heap_block_t *heap_head = 0;
os_mutex_t mutex_heap;

void os_heap_init(){
    os_mutex_init(&mutex_heap);
    heap_head = (heap_block_t *)os_heap;
    heap_head->is_free = 1;
    heap_head->size = SIZE_RAM - sizeof(heap_block_t);
    heap_head->next = 0;
}

void* os_malloc(uint32_t size){
    os_mutex_take(&mutex_heap);
    heap_block_t *current = heap_head;
    while(current != 0){
        if(current->is_free == 1 && current->size >= size){
            if(current->size >= size+sizeof(heap_block_t)+1){
                heap_block_t *new = current;
                new = (heap_block_t *)((uint8_t *)current + sizeof(heap_block_t) + size);
                new->is_free = 1;
                new->size = current->size - size - sizeof(heap_block_t);
                new->next = current->next;
                current->is_free = 0;
                current->size = size;
                current->next = new;
            }
            else{
                current->is_free = 0;
            }
            os_mutex_give(&mutex_heap);
            return (void*)((uint8_t *)current + sizeof(heap_block_t));
        }
        current = current->next;
    }
    os_mutex_give(&mutex_heap);
    return 0;
}

void os_mfree(void *mem){
    if(mem == 0){
        return;
    }
    os_mutex_take(&mutex_heap);
    heap_block_t *block = (heap_block_t *)((uint8_t *)mem - sizeof(heap_block_t));
    block->is_free = 1;
    heap_block_t *current = heap_head;
    while(current->next != 0){
        if(current->is_free == 1 && current->next->is_free == 1){
            current->size = current->size + sizeof(heap_block_t) + current->next->size;
            current->next = current->next->next;
        }
        else{
            current=current->next;
        }
    }
    os_mutex_give(&mutex_heap);
}