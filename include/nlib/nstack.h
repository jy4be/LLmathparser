#ifndef _H_NSTACK
#define _H_NSTACK

#include <stdbool.h>
#include "nheap.h"

typedef struct Stack_frame_t {
    size_t size;
    size_t index;
    allocator_t alloc;
} stack_frame_t;

#define stack_t(T) \
    struct { \
        union { \
            T *stack_pointer; \
            T variable_type; \
        }; \
        stack_frame_t frame; \
    }

void *nstk_setup_frame__(
        stack_frame_t *frame,
        size_t size,
        size_t element_size,
        allocator_t alloc);
bool nstk_push__(stack_frame_t *frame);
bool nstk_pop__(stack_frame_t *frame);
size_t nstk_size__(stack_frame_t *frame);
void nstk_destroy__(stack_frame_t *frame, void *stack_pointer);

#define nstk_setup(stack, size, alloc) \
    stack.stack_pointer = nstk_setup_frame__( \
            &stack.frame,\
            size, \
            sizeof(stack.variable_type), \
            alloc)

//It do be hacky, but it do be worky
#define nstk_push(stack, element) \
    nstk_push__(&stack.frame) ? \
        (stack.stack_pointer[nstk_size__(&stack.frame)] = element, true) : \
        false

#define nstk_top(stack) stack.stack_pointer[nstk_size__(&stack.frame)]
#define nstk_pop(stack) nstk_pop__(&stack.frame)
#define nstk_size(stack) nstk_size__(&stack.frame)

#define nstk_destroy(stack) \
    nstk_destroy__(&stack.frame, (void*) stack.stack_pointer)


#endif //_H_NSTACK
