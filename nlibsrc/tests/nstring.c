#include <stdbool.h>

#include "nlib/nstring.h"

#include "nlib/test.h"
#include "nlib/nheap.h"
#include "nlib/stdalloc.h"


int main() {
    TEST_SUITE("nstr_length_from_cstr") {
        IS_EQUAL(nstr_length_from_raw("", 0), 0, "Empty String has length 0");
        IS_EQUAL(nstr_length_from_raw("1234567", 0), 7, "Automatically identifies length correctly");
        IS_EQUAL(nstr_length_from_raw("1234567", 4), 4, "Respects Maximum length");
        IS_EQUAL(nstr_length_from_raw("1234567", 10), 7, "Determines Length correctly with maximum length");
    }

    TEST_SUITE("nstr_str_from_cstr") {
        const char test_cstr[] = "Test";
        str_t test_str = nstr_str_from_cstr(test_cstr);

        IS_EQUAL(test_str.length, 4, "String Length Correctly Determined");
        IS_EQUAL(test_str.raw, test_cstr, "String Pointer is Equal");
    }

    TEST_SUITE("nstr_str_from_unbound_raw") {

        const char test_unbound_cstr[] = "awjkwsezuifpseifasepöugasbeifbpaesfgbaesfuzvasklfgasolfgvaseolfzvasef";
        const char test_cstr[] = "Test";
        str_t test_unbound_str = nstr_str_from_unbound_raw(test_unbound_cstr, 20);
        str_t test_bound_str = nstr_str_from_unbound_raw(test_cstr, 20);

        IS_EQUAL(test_unbound_str.length, 20, "Unbound String Length Correct");
        IS_EQUAL(test_unbound_str.raw, test_unbound_cstr, "String Pointer is Equal");

        IS_EQUAL(test_bound_str.length, 4, "Bound String Length Correct");
        IS_EQUAL(test_bound_str.raw, test_cstr, "String Pointer is Equal");
    }
    
    TEST_SUITE("nstr_find_char") {
        const char *test_cstr = "abcdefghijklmnopqrstuvwxyz";
        str_t test_str = nstr_str_from_cstr(test_cstr);

        IS_EQUAL(nstr_str_find_char(test_str, 'l'), 11, "Finds correct index");
        IS_EQUAL(nstr_str_find_char(test_str, ' '), INVALID_INDEX, "Cannot find char that is not present");
    } 
    TEST_SUITE("nstr_slice") {
        const char *test_cstr = "123456";
        str_t test_str = nstr_str_from_cstr(test_cstr);

        str_t slice1 = nstr_str_slice(test_str, 0, 3);
        IS_EQUAL(slice1.length, 3, "Slice has correct length");
        IS_EQUAL(slice1.raw, test_cstr, "String Pointer is Equal");

        str_t slice2 = nstr_str_slice(test_str, 1, 0);
        IS_EQUAL(slice2.is_valid, false, "Cannot create slice when end < start");

        str_t slice3 = nstr_str_slice(test_str, 7, 8);
        IS_EQUAL(slice3.is_valid, false, "Cannot create slice when index is out of bounds");
    }

    TEST_SUITE("nstr_is_equal") {
        const char *test_cstr1 = "aaa";
        const char *test_cstr2 = "bbbb";

        str_t test_str1 = nstr_str_from_cstr(test_cstr1);
        str_t test_str2 = nstr_str_from_cstr(test_cstr1);
        str_t test_str3 = nstr_str_from_cstr(test_cstr2);

        IS_EQUAL(nstr_str_is_equal(test_str1, test_str2), true, "Equal strings return true");
        IS_EQUAL(nstr_str_is_equal(test_str1, test_str3), false, "Unequal strings return false");
    }

    TEST_SUITE("nstr_has_equal_part") {
        const char *test_cstr1 = "1234 equal";
        const char *test_cstr2 = "abcd equal";
        const char *test_cstr3 = "unequal";

        str_t test_str1 = nstr_str_from_cstr(test_cstr1);
        str_t test_str2 = nstr_str_from_cstr(test_cstr2);
        str_t test_str3 = nstr_str_from_cstr(test_cstr3);

        IS_EQUAL(nstr_str_has_equal_part(test_str1, test_str2, 0, 10), false, "Unequal Parts of string return False");
        IS_EQUAL(nstr_str_has_equal_part(test_str1, test_str2, 5, 5), true, "Equal Parts of string return True");
        IS_EQUAL(nstr_str_has_equal_part(test_str1, test_str3, 0, 10), false, "different length strings return false when length is too long");
    }

    TEST_SUITE("nstr_find_string") {
        const char *test_cstr1 = "abcdefghij";
        const char *test_cstr2 = "ghi";
        const char *test_cstr3 = "123";

        str_t test_str1 = nstr_str_from_cstr(test_cstr1);
        str_t test_str2 = nstr_str_from_cstr(test_cstr2);
        str_t test_str3 = nstr_str_from_cstr(test_cstr3);

        IS_EQUAL(nstr_str_find_string(test_str1, test_str2), 6, "Finds String with correct index");
        IS_EQUAL(nstr_str_find_string(test_str1, test_str3), INVALID_INDEX, "Cannot find pattern in wrong string");
    }

    TEST_SUITE("nstr_buffer_from_str") {
        const char *test_cstr = "test12345";
        str_t test_str = nstr_str_from_cstr(test_cstr);

        str_buffer_t test_buffer = nstr_buffer_from_str(test_str, stdalloc);

        IS_TRUE(test_buffer.is_valid, "Buffer is valid");
        IS_EQUAL(test_buffer.length, 9, "Length determined correctly");
        IS_EQUAL(test_buffer.capacity, 10, "Capacity determined correctly");

        test_buffer.buffer[3] = 'f';
        IS_EQUAL(test_buffer.buffer[3], 'f', "Buffer is editable");

        test_buffer.alloc.proc(&test_buffer.alloc, 0, test_buffer.buffer);
    }

    TEST_SUITE("nstr_destroy_buffer") {
        const char *test_cstr = "test12345";
        str_t test_str = nstr_str_from_cstr(test_cstr);

        str_buffer_t test_buffer = nstr_buffer_from_str(test_str, stdalloc);
        IS_TRUE(test_buffer.is_valid, "Buffer is valid");

        nstr_destroy_buffer(&test_buffer);
        IS_EQUAL(test_buffer.is_valid, false, "Buffer is invalid after destroying");
    }

    TEST_SUITE("nstr_str_from_buffer") {
        const char *test_cstr = "test12345";
        str_t test_str = nstr_str_from_cstr(test_cstr);

        str_buffer_t test_buffer = nstr_buffer_from_str(test_str, stdalloc);

        const str_t buffer_test_str = nstr_str_from_buffer(test_buffer);
        IS_TRUE(nstr_str_is_equal(buffer_test_str, nstr_str_from_cstr(test_cstr)), "Buffer and String are equal");

        nstr_destroy_buffer(&test_buffer);
    }

    TEST_SUITE("nstr_expand_buffer") {
        const char *test_cstr = "test12345";
        str_t test_str = nstr_str_from_cstr(test_cstr);

        str_buffer_t test_buffer = nstr_buffer_from_str(test_str, stdalloc);

        nstr_expand_buffer(&test_buffer, 20);
        IS_EQUAL(test_buffer.capacity, 20, "Buffer has correct capacity");

        nstr_expand_buffer(&test_buffer, 10);
        IS_EQUAL(test_buffer.capacity, 20, "Buffer cannot shrink");
        
        nstr_destroy_buffer(&test_buffer);
    }

    TEST_SUITE("nstr_buffer_append") {
        const char *test_cstr1 = "Hello, ";
        const char *test_cstr2 = "World!";
        str_t test_str1 = nstr_str_from_cstr(test_cstr1);

        str_buffer_t test_buffer = nstr_buffer_from_str(test_str1, stdalloc);
        str_t test_str = nstr_str_from_cstr(test_cstr2);

        nstr_buffer_append(&test_buffer, test_str);
        IS_TRUE(nstr_str_is_equal(nstr_str_from_buffer(test_buffer), nstr_str_from_cstr("Hello, World!")),
                "Appended Buffer Contains correct String");

        IS_EQUAL(test_buffer.length, 13, "Buffer has correct length");
        IS_EQUAL(test_buffer.capacity, 14, "Buffer has correct capacity");
        IS_TRUE(test_buffer.is_valid, "Buffer is valid");

        nstr_destroy_buffer(&test_buffer);
    }

    TEST_SUITE("nstr_buffer_insert") {
        const char *test_cstr1 = "HelloWorld";
        const char *test_cstr2 = ", new ";
        str_t test_str1 = nstr_str_from_cstr(test_cstr1);

        str_buffer_t test_buffer = nstr_buffer_from_str(test_str1, stdalloc);
        str_t test_str = nstr_str_from_cstr(test_cstr2);

        nstr_buffer_insert(&test_buffer, 5, test_str);

        IS_TRUE(nstr_str_is_equal(nstr_str_from_buffer(test_buffer), nstr_str_from_cstr("Hello, new World")),
                "Inserted buffer contains correct String");

        IS_EQUAL(test_buffer.length, 16, "Buffer has correct length");
        IS_EQUAL(test_buffer.capacity, 17, "Buffer has correct capacity");
        IS_TRUE(test_buffer.is_valid, "Buffer is valid");
    }

    TEST_SUITE("nstr_buffer_remove") {
        const char *test_cstr = "Hello, cruel World!";
        str_t test_str = nstr_str_from_cstr(test_cstr);

        str_buffer_t test_buffer = nstr_buffer_from_str(test_str, stdalloc);

        nstr_buffer_remove(&test_buffer, 7, 13);

        IS_TRUE(nstr_str_is_equal(nstr_str_from_buffer(test_buffer), nstr_str_from_cstr("Hello, World!")),
                "Removed from Buffer contains correct String");

        IS_EQUAL(test_buffer.length, 13, "Buffer has correct length");
        IS_EQUAL(test_buffer.capacity, 20, "Buffer has correct capacity");
        IS_TRUE(test_buffer.is_valid, "Buffer is valid");
    }

    TEST_SUITE("nstr_clone_buffer") {
        const char *test_cstr = "test12345";
        str_t test_str = nstr_str_from_cstr(test_cstr);

        str_buffer_t test_buffer = nstr_buffer_from_str(test_str, stdalloc);
        str_buffer_t cloned_buffer = nstr_clone_buffer(test_buffer);

        IS_TRUE(cloned_buffer.is_valid, "Cloned Buffer is valid");
        IS_TRUE(nstr_str_is_equal(nstr_str_from_buffer(test_buffer), nstr_str_from_buffer(cloned_buffer)), "Cloned Buffer contains same string");

        nstr_destroy_buffer(&test_buffer);
        nstr_destroy_buffer(&cloned_buffer);
    }

    TEST_SUITE("nstr_cstr_from_str") {
        const char *test_cstr = "test12345";
        char buffer[20] = {0};

        str_t test_str = nstr_str_from_cstr(test_cstr);

        bool result = nstr_cstr_from_str(test_str, buffer);

        IS_TRUE(result, "Buffer was copied");
        IS_EQUAL(buffer[9], '\0', "String is null-terminated correctly");
    }

    TEST_SUITE("nstr_split_at") {
        const char *test_cstr = "ab/cd/ef";
        const char *after_split = "cd/ef";

        str_t test_str = nstr_str_from_cstr(test_cstr);
        str_t cut_str = nstr_str_split_at(&test_str, '/');

        IS_TRUE(cut_str.is_valid, "Split off string is valid");
        IS_EQUAL(cut_str.length, 3, "Split off string has correct length");
        IS_EQUAL(cut_str.raw, test_cstr, "Pointers are equal");

        str_t comp_str = nstr_str_from_cstr(after_split);
        IS_TRUE(nstr_str_is_equal(test_str, comp_str), "remainig string is correct");

        const char *test_cstr2 = "ef/";
        const char *after_split2 = "";

        str_t test_str2 = nstr_str_from_cstr(test_cstr2);
        nstr_str_split_at(&test_str2, '/');
        str_t comp_str2 = nstr_str_from_cstr(after_split2);
        
        IS_EQUAL(test_str2.length, 0, "remainig string with delimiter in last spot has correct length");
        IS_TRUE(nstr_str_is_equal(test_str2, comp_str2), "remainig string is empty");
    }


    RESULT();
}
