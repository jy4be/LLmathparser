#ifndef _H_NGENSTR
#define _H_NGENSTR

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "nheap.h"
#include "nstring.h"

inline str_t nstr_return_self_str__(str_t to_return) {
    return to_return;
}

#define nstr_to_str(str) \
    _Generic((str), \
            str_t: nstr_return_self_str__, \
            const str_t: nstr_return_self_str__, \
            str_buffer_t: nstr_str_from_buffer, \
            const str_buffer_t: nstr_str_from_buffer, \
            char*: nstr_str_from_cstr, \
            const char*: nstr_str_from_cstr)(str)

#define nstr_new_buffer(str, alloc) \
    nstr_buffer_from_str(nstr_to_str(str), alloc)

#define nstr_find_char(source, target) \
    nstr_str_find_char(nstr_to_str(source), target)

#define nstr_find_string(source, pattern) \
    nstr_str_find_string(nstr_to_str(source), nstr_to_str(pattern))

#define nstr_is_equal(a, b) \
    nstr_str_is_equal(nstr_to_str(a), nstr_to_str(b))

#define nstr_has_equal_part(a, b, start, stop) \
    nstr_str_has_equal_part( \
            nstr_to_str(a), \
            nstr_to_str(b), \
            start, \
            stop)

#define nstr_slice(source, start, end) \
    nstr_str_slice(nstr_to_str(source), start, end)


#endif // _H_NGENSTR
