#include "dmem.h"

#include <stdlib.h>

alloc_t ualloc = malloc;
dealloc_t ufree = free;
realloc_t urealloc = realloc;

