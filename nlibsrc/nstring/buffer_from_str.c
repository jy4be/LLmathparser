#include <stddef.h>
#include <stdbool.h>

#include "nlib/nstring.h"
#include "nlib/nheap.h"

str_buffer_t nstr_buffer_from_str(
        const str_t nstring,
        const allocator_t alloc)
{
    if (!nstring.is_valid)
        return (str_buffer_t) {false, 0, 0, NULL, alloc};

    size_t length = nstring.length;

    char *str_buffer = (char*) alloc.proc(&alloc, length + 1, NULL);
    if (!str_buffer)
        return (str_buffer_t) {.is_valid = false};

    for (size_t i = 0; i < length; i++) {
        str_buffer[i] = nstring.raw[i];
    }
    str_buffer[length] = '\0';

    return (str_buffer_t) {true, length, length + 1, str_buffer, alloc};
}
