#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "nlib/nstring.h"

str_index_t nstr_str_find_string(const str_t source, const str_t pattern) {
    if (!source.is_valid || !pattern.is_valid) 
        return INVALID_INDEX;

    if (source.length == 0 || pattern.length == 0)
        return INVALID_INDEX;
        
    str_index_t next_occurence;
    str_t compare_slice;
    str_t source_slice = nstr_str_slice(
            source,
            0,
            source.length-1);

    do {
        next_occurence = nstr_str_find_char(source_slice, pattern.raw[0]);
        compare_slice = nstr_str_slice(
                source_slice,
                next_occurence,
                next_occurence + pattern.length);

        if (nstr_str_is_equal(compare_slice, pattern)) 
            return compare_slice.raw - source.raw;
        source_slice = nstr_str_slice(
                source_slice,
                next_occurence,
                source_slice.length-1);
    } while (next_occurence != INVALID_INDEX);
    
    return INVALID_INDEX;
}
