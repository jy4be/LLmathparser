#include <stdbool.h>
#include <stddef.h>

#include "nlib/nstring.h"
#include "nlib/nheap.h"

void nstr_buffer_remove(
        str_buffer_t *buffer,
        const str_index_t start,
        const str_index_t end)
{
    if (!buffer->is_valid || start == INVALID_INDEX || end == INVALID_INDEX) {
        nstr_destroy_buffer(buffer);
        return;
    }

    if (end > buffer->length || start > end) {
        nstr_destroy_buffer(buffer);
        return;
    }

    size_t cut_length = end - start;

    for(size_t i = end; i < buffer->length; i++) 
        buffer->buffer[i - cut_length] = buffer->buffer[i];

    buffer->length -= cut_length;
    buffer->buffer[buffer->length] = '\0';
}
