/* Inspired by the "Modern C" talk by Luca Sass
 *
 */
#ifndef _H_NSTRING
#define _H_NSTRING

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "nheap.h"


#define INVALID_INDEX SIZE_MAX

/* Index size used is System-dependent. Since ssize_t is non-standard, 
 * normal size_t is used and a value of MAX_SIZE indicates an 
 * invalid index. Thank Microsoft not adapting POSIX for this.
 */
typedef size_t str_index_t;

typedef struct String_S {
    bool is_valid;
    size_t length;
    const char *raw;
} str_t;

typedef struct String_Buffer_S {
    bool is_valid;
    size_t length;
    size_t capacity;
    char *buffer;
    const allocator_t alloc;
} str_buffer_t;

/* C-String Functions */
size_t nstr_length_from_raw(const char *raw_string, size_t max_length);

/* Static string functions*/
str_t nstr_str_from_cstr(const char *raw_string);
str_t nstr_str_from_unbound_raw(const char *raw_string, size_t max_length);
bool nstr_cstr_from_str(const str_t source, char* cstr_buffer);

str_index_t nstr_str_find_char(const str_t source, const char target);
str_index_t nstr_str_find_string(const str_t source, const str_t pattern);

bool nstr_str_is_equal(const str_t a, const str_t b);
bool nstr_str_has_equal_part(
        const str_t a, 
        const str_t b, 
        str_index_t start,
        str_index_t length);

str_t nstr_str_slice(const str_t source, str_index_t start, str_index_t end);
str_t nstr_str_split_at(str_t *source, char delimiter);

/* Mutable String Functions */
str_buffer_t nstr_buffer_from_str(
        const str_t nstring,
        const allocator_t alloc);
void nstr_destroy_buffer(str_buffer_t *buffer);
str_t nstr_str_from_buffer(str_buffer_t buffer);
str_buffer_t nstr_clone_buffer(const str_buffer_t original);
void nstr_expand_buffer(str_buffer_t *buffer, size_t min_size);

void nstr_buffer_append(str_buffer_t *buffer, str_t str_to_add);
void nstr_buffer_insert(
        str_buffer_t *buffer, 
        const str_index_t index_to_insert, 
        const str_t str_to_insert);
void nstr_buffer_remove(
        str_buffer_t *buffer,
        const str_index_t start,
        const str_index_t end);

//Uppercase-Lowercase functions, map function to character 

#endif //_H_NSTRING
