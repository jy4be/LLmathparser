#include <stdbool.h>
#include <stddef.h>

#include "nlib/nstring.h"
#include "nlib/nheap.h"


str_t nstr_str_split_at(str_t *source, char delimiter) {
    if (!source->is_valid)
        return (str_t) {.is_valid=false};

    str_index_t del_index = nstr_str_find_char(*source, delimiter);
    
    str_t clone_str;
    if (del_index == INVALID_INDEX) {
        clone_str = *source;

        source->raw += source->length;
        source->length = 0;
    }
    else {
        clone_str = nstr_str_slice(*source, 0, del_index + 1);

        source->raw += del_index + 1;
        source->length -= del_index + 1;
    }
    
    return clone_str;
}
