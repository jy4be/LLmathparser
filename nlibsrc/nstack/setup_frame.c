#include "nlib/nstack.h"
#include <stdint.h>

void *nstk_setup_frame__(
        stack_frame_t *frame,
        size_t size,
        size_t element_size,
        allocator_t alloc)
{
   frame->size = size;
   frame->index = 0;
   frame->alloc = alloc;

   char *stack_pointer = alloc.proc(&alloc, (size + 1) * element_size, NULL);

   for (size_t i = 0; i < element_size; i++) 
       stack_pointer[i] = 0;

   return (void*) stack_pointer;
}
