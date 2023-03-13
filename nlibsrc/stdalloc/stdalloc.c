#include <stdlib.h>

#include "nlib/stdalloc.h"


void *stdalloc_wrapper(
        const allocator_t *this_allocator,
        size_t amount_to_allocate,
        void *pointer_to_free)
{
    free(pointer_to_free);
    if (amount_to_allocate > 0)
        return malloc(amount_to_allocate);
    else
        return NULL;
}

const allocator_t stdalloc = (allocator_t) {NULL, *stdalloc_wrapper};
