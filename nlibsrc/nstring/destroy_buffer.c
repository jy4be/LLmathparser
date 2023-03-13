#include <stddef.h>
#include <stdbool.h>

#include "nlib/nstring.h"
#include "nlib/nheap.h"


void nstr_destroy_buffer(str_buffer_t *buffer) {
    if (!buffer)
        return;
    if (!buffer->is_valid)
        return;
    if (buffer->capacity == 0)
        return;

    buffer->alloc.proc(&buffer->alloc, 0, buffer->buffer);
    buffer->is_valid = false;
}
