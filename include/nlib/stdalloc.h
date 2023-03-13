#ifndef _H_STDALLOC
#define _H_STDALLOC

#include <stddef.h>

#include "nheap.h"


void *stdalloc_wrapper(
        const allocator_t *this_allocator,
        size_t amount_to_allocate,
        void *pointer_to_free);

extern const allocator_t stdalloc;

#endif //_H_STDALLOC
