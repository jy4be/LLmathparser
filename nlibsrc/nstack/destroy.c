#include "nlib/nstack.h"

void nstk_destroy__(stack_frame_t *frame, void *stack_pointer) {
    frame->size = 0;
    frame->index = 0;

    frame->alloc.proc(&frame->alloc, 0, stack_pointer);
}

