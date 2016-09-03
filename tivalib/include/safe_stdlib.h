#ifndef _SAFE_STDLIB_H
#define _SAFE_STDLIB_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

void safe_init(void);
void* safe_malloc (size_t size);
void* safe_calloc (size_t num, size_t size);
void* safe_realloc (void* ptr, size_t size);
void safe_free(void* ptr);

#ifdef __cplusplus
}
#endif

#endif// _SAFE_STDLIB_H
