#include "safe_stdlib.h"
#include "cmsis_os.h"

osMutexDef (safe_stdlib_mutex_def);
osMutexId safe_stdlib_mutex_id;

void safe_init(void){
    safe_stdlib_mutex_id = osMutexCreate(osMutex(safe_stdlib_mutex_def));
}

void* safe_malloc (size_t size){
    void* ptr  = NULL;
    osMutexWait(safe_stdlib_mutex_id,osWaitForever);
    ptr = malloc(size);
    osMutexRelease(safe_stdlib_mutex_id);
    return ptr;
}

void* safe_calloc (size_t num, size_t size){
    void* ptr  = NULL;
    osMutexWait(safe_stdlib_mutex_id,osWaitForever);
    ptr = calloc(num,size);
    osMutexRelease(safe_stdlib_mutex_id);
    return ptr;
}

void* safe_realloc (void* ptr, size_t size){
    osMutexWait(safe_stdlib_mutex_id,osWaitForever);
    ptr = realloc(ptr,size);
    osMutexRelease(safe_stdlib_mutex_id);
    return ptr;
}

void safe_free(void* ptr){
    osMutexWait(safe_stdlib_mutex_id,osWaitForever);
    free(ptr);
    osMutexRelease(safe_stdlib_mutex_id);
}
