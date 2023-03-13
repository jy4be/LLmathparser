#include <stdbool.h>
#include <stddef.h>

#include "nlib/nstring.h"

/* This funczion creates a string from a c_string
 */
str_t nstr_str_from_cstr(const char *raw_string) {
    size_t length = nstr_length_from_raw(raw_string, 0);
    return (str_t) {true, length, raw_string};
}

/* This functions creates a string from a c_string;
 * The length of the resulting string is 'max_length'
 * or until the 0 terminator in the c-string if one is found.
 */
str_t nstr_str_from_unbound_raw(const char *raw_string, size_t max_length) {
    if (max_length) {
        size_t length = nstr_length_from_raw(raw_string, max_length);
        return (str_t) {true, length, raw_string};
    }
    else {
        return (str_t) {true, 0, raw_string};
    }
}
