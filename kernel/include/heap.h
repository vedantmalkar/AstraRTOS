#ifndef H_HEAP
#define H_HEAP

#include <stdint.h>

typedef struct heap_block {
    uint32_t size;
    uint8_t is_free;
    struct heap_block *next;
} heap_block_t;

void os_heap_init();
void* os_malloc(uint32_t size);
void os_mfree(void* mem);

#endif