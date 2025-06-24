#include <stddef.h>
#include <stdint.h>

void *memcpy(void *dest, const void *src, size_t count) {
    uint8_t *d = dest;
    const uint8_t *s = src;
    for (size_t i = 0; i < count; i++) {
        d[i] = s[i];
    }
    return dest;
}

void *memset(void *dest, int value, size_t count) {
    uint8_t *d = dest;
    for (size_t i = 0; i < count; i++) {
        d[i] = (uint8_t)value;
    }
    return dest;
}

size_t strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int strcmp(const char *a, const char *b) {
    while (*a && (*a == *b)) {
        a++;
        b++;
    }
    return *(const unsigned char*)a - *(const unsigned char*)b;
}

static uint32_t alloc_base = 0;
static uint32_t alloc_limit = 0;

void init_allocator(uint32_t base, uint32_t length) {
	alloc_base = base;
	alloc_limit = base + length;
}

void* kmalloc(uint32_t size) {
	if (alloc_base + size > alloc_limit)
		return 0; //out of memory
	

	void* result = (void*)alloc_base;
	alloc_base += size;
	return result;
}
