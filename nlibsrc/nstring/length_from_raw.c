#include <stddef.h>

#include "nlib/nstring.h"

/* Returns the length of "raw_string".
 * This function searches the string until it findes the0-Terminator,
 * or until it hits 'max_length'. 'max_length' of 0 ignores 'max_length'.
 *
 * */
size_t nstr_length_from_raw(const char *raw_string, size_t max_length) {
    size_t index = 0;

    if (max_length) {
        while(raw_string[index] && index < max_length) 
            index++;
    }

    else {
        while(raw_string[index])
            index++;
    }

    return index;

}
