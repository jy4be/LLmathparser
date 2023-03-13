#include <stddef.h>
#include <stdbool.h>

#include "nlib/nstring.h"
#include "nlib/nheap.h"

str_t nstr_str_from_buffer(str_buffer_t buffer) {
    if (!buffer.is_valid)
        return (str_t) {.is_valid = 0};
    return (str_t) {true, buffer.length, buffer.buffer};
}
