/* Inspired by the "Modern C" talk by Luca Sass
 *
 */
#ifndef _H_NHEAP
#define _H_NHEAP

#include <stddef.h>
#include <stdbool.h>

#define nheap_alloc(alloc, size) alloc.proc(&alloc, size, NULL)
#define nheap_dealloc(alloc, pointer) alloc.proc(&alloc, 0, pointer)

typedef struct Allocator_S {
    void *user_data;
    void *(*proc) (
        const struct Allocator_S *this_allocator,
        size_t amount_to_allocate,
        void *pointer_to_free);
} allocator_t;

#endif //_H_NHEAP
