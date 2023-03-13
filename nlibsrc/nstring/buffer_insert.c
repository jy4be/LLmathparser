#include <stdbool.h>
#include <stddef.h>

#include "nlib/nstring.h"
#include "nlib/nheap.h"

void nstr_buffer_insert(
        str_buffer_t *buffer, 
        const str_index_t index_to_insert, 
        const str_t str_to_add) 
{
    if (!buffer->is_valid || 
        index_to_insert == INVALID_INDEX || 
        !str_to_add.is_valid) 
    {
        nstr_destroy_buffer(buffer);
        return;
    }

    size_t new_length = buffer->length + str_to_add.length;

    nstr_expand_buffer(buffer, new_length + 1);

    if (!buffer->is_valid) 
        return;
    
    for (size_t i = index_to_insert + str_to_add.length - 1; 
         i >= index_to_insert; 
         i--) 
    {
        buffer->buffer[i + str_to_add.length] = buffer->buffer[i];
        buffer->buffer[i] = str_to_add.raw[i - index_to_insert];
    }

    buffer->buffer[new_length] = '\0';
    buffer->length = new_length;
}

