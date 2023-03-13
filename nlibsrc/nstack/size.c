#include "nlib/nstack.h"

size_t nstk_size__(stack_frame_t *frame) {
    return frame->index;
}
