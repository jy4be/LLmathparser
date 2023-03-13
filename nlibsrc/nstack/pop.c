#include <stdbool.h>

#include "nlib/nstack.h"

bool nstk_pop__(stack_frame_t *frame) {
    if (frame->index > 0) {
        frame->index--;
        return true;
    }
    else return false;
}
