#include <stdbool.h>
#include <stddef.h>

#include "nlib/nstring.h"
#include "nlib/nheap.h"

bool nstr_cstr_from_str(const str_t source, char* cstr_buffer) {
    if (!source.is_valid)
        return false;

    for (size_t i = 0; i < source.length; i++)
        cstr_buffer[i] = source.raw[i];
    cstr_buffer[source.length] = '\0';

    return true;
}
