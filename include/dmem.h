#ifndef ___DMEM_H__
#define ___DMEM_H__

#include "types.h"

/**
 * Function pointer to the function used to allocate memory dynamically.
 */
extern alloc_t ualloc;

/**
 * Function pointer to the function used to deallocate dynamically allocated
 * memory.
 */
extern dealloc_t ufree;

/**
 * Funtion pointer to the function used to resize dynamically allocated memory.
 */
extern realloc_t urealloc;

#endif //___DMEM_H__
