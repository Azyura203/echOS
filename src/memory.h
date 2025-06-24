#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void *memcpy(void *dest, const void *src, size_t count);
void *memset(void *dest, int value, size_t count);
size_t strlen(const char *str);
int strcmp(const char *a, const char *b);
void init_allocator(uint32_t base, uint32_t length);
void* kmalloc(uint32_t size);

#endif
