#include <stdbool.h>
#include <stddef.h>

#include "nlib/nstring.h"
#include "nlib/nheap.h"

void nstr_expand_buffer(str_buffer_t *buffer, size_t min_size) {
    //Error checking
    if (!buffer->is_valid) {
        nstr_destroy_buffer(buffer);
        return;
    }

    if (buffer->capacity >= min_size)
        return;

    //Allocate new Buffer and errorcheck allocation
    char *new_buffer = buffer->alloc.proc(
            &buffer->alloc,
            min_size,
            NULL);
    if (!new_buffer) {
        nstr_destroy_buffer(buffer);
        return;
    }

    //Copy old data over
    for (size_t i = 0; i < buffer->capacity; i++) {
        new_buffer[i] = buffer->buffer[i];
    }

    buffer->alloc.proc(&buffer->alloc, 0, buffer->buffer);

    buffer->capacity = min_size;
    buffer->buffer = new_buffer;
}
