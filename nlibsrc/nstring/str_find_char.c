#include <stddef.h>
#include <stdbool.h>

#include "nlib/nstring.h"

str_index_t nstr_str_find_char(const str_t source, const char target) {
    if (!source.is_valid) return INVALID_INDEX;

    for(size_t index = 0; index < source.length; index++)
        if (source.raw[index] == target)
            return index;

    return INVALID_INDEX;

}
