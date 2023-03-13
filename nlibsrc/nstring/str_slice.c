#include <stddef.h>
#include <stdbool.h>

#include "nlib/nstring.h"

/* Creates slice of some String
 */
str_t nstr_str_slice(
        const str_t source, 
        const str_index_t start, 
        const str_index_t end) 
{
    if (!source.is_valid || start == INVALID_INDEX || end == INVALID_INDEX) 
        return (str_t) {false, 0, NULL};

    if (start > end)
        return (str_t) {false, 0, NULL};

    if ((size_t) end > source.length)
        return (str_t) {false, 0, NULL};

    return (str_t) {
        true, 
        end - start, 
        source.raw + start};

}
