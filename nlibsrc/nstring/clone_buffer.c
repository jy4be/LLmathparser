#include <stdbool.h>
#include <stddef.h>

#include "nlib/nstring.h"
#include "nlib/nheap.h"


str_buffer_t nstr_clone_buffer(const str_buffer_t original) {
    if (!original.is_valid)
        return (str_buffer_t) {.is_valid=false};

    char *cloned_buffer = (char*) original.alloc.proc(
            &original.alloc,
            original.capacity,
            NULL);

    if (!cloned_buffer)
        return (str_buffer_t) {.is_valid=false};

    for (size_t i = 0; i < original.length + 1; i++) {
       cloned_buffer[i] = original.buffer[i];
    }

    return (str_buffer_t) {
        true, 
        original.length,
        original.capacity,
        cloned_buffer,
        original.alloc};
}
