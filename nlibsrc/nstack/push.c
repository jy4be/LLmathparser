#include <stdbool.h>

#include "nlib/nstack.h"

bool nstk_push__(stack_frame_t *frame) {
    if (frame->index < frame->size) {
        frame->index++;
        return true;
    }
    else 
        return false;
}
