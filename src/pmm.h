#ifndef PMM_H
#define PMM_H

#include <stdint.h>

void pmm_init(uint32_t base, uint32_t length);
void* pmm_alloc();
void pmm_free(void* addr);
uint32_t pmm_get_free_pages();

#endif
