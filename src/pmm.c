#include "pmm.h"
#include "vga.h"
#include <stddef.h>
#include <stdint.h>

#define PAGE_SIZE 4096
#define MAX_PAGES 32768  // enough to track 128MB of RAM (32768 x 4KB)

static uint8_t bitmap[MAX_PAGES / 8];  // Each bit = 1 page
static uint32_t memory_base = 0;
static uint32_t total_pages = 0;

static inline void set_bit(int bit)   { bitmap[bit / 8] |=  (1 << (bit % 8)); }
static inline void clear_bit(int bit) { bitmap[bit / 8] &= ~(1 << (bit % 8)); }
static inline int  test_bit(int bit)  { return bitmap[bit / 8] & (1 << (bit % 8)); }

void pmm_init(uint32_t base, uint32_t length) {
    memory_base = base;
    total_pages = length / PAGE_SIZE;
    for (uint32_t i = 0; i < total_pages; i++)
        clear_bit(i);  // Mark all pages as free
}

void* pmm_alloc() {
    for (uint32_t i = 0; i < total_pages; i++) {
        if (!test_bit(i)) {
            set_bit(i);
            return (void*)(memory_base + i * PAGE_SIZE);
        }
    }
    return NULL; // No memory available
}

void pmm_free(void* addr) {
    uint32_t index = ((uint32_t)addr - memory_base) / PAGE_SIZE;
    if (index < total_pages)
        clear_bit(index);
}

uint32_t pmm_get_free_pages() {
    uint32_t count = 0;
    for (uint32_t i = 0; i < total_pages; i++)
        if (!test_bit(i)) count++;
    return count;
}
