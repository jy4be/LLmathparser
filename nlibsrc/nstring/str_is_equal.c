#include <stddef.h>
#include <stdbool.h>

#include "nlib/nstring.h"


bool nstr_str_is_equal(const str_t a, const str_t b) {
    if (!a.is_valid || !b.is_valid)
        return false;

    if (a.length != b.length)
        return false;

    for (size_t i = 0; i < a.length; i++) {
        if (a.raw[i] != b.raw[i])
            return false;
    }

    return true;
}

bool nstr_str_has_equal_part(
        const str_t a, 
        const str_t b, 
        str_index_t start,
        str_index_t length)
{
    if (!a.is_valid || !b.is_valid)
        return false;

    if (start == INVALID_INDEX || length == INVALID_INDEX)
        return false;

    if (a.length < start + length || b.length < start + length)
        return false;

    if (a.length < start || b.length < start)
        return false;

    for (size_t i = start; i < start + length; i++) {
        if (a.raw[i] != b.raw[i])
            return false;
    }

    return true;
}
