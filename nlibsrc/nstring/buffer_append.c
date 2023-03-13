#include <stdbool.h>
#include <stddef.h>

#include "nlib/nstring.h"
#include "nlib/nheap.h"

void nstr_buffer_append(str_buffer_t *buffer, str_t str_to_add) {
    if (!buffer->is_valid || !str_to_add.is_valid){
        nstr_destroy_buffer(buffer);
        return;
    }

    size_t new_length = buffer->length + str_to_add.length;

    nstr_expand_buffer(buffer, new_length + 1);

    if (!buffer->is_valid) {
        return;
    }
    
    for (size_t i = 0; i < str_to_add.length; i++) 
        buffer->buffer[i + buffer->length] = str_to_add.raw[i];
    buffer->buffer[new_length] = '\0';

    buffer->length = new_length;
}
