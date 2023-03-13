#include "nlib/ngenstr.h"
#include "nlib/test.h"
#include "nlib/stdalloc.h"

int main() {

    TEST_SUITE("nstr_to_cstr") {
        str_t str1 = nstr_to_str(nstr_str_from_cstr("test"));

        str_t str2 = nstr_to_str("test2");

        str_buffer_t buffer = nstr_buffer_from_str(nstr_str_from_cstr("test3"), stdalloc);

        str_t str3 = nstr_to_str(buffer);

        IS_TRUE(str1.is_valid, "Validity of normal string");
        IS_TRUE(str2.is_valid, "Validity of c string");
        IS_TRUE(str3.is_valid, "Validity of buffer string");

        nstr_destroy_buffer(&buffer);
    }

    TEST_SUITE("nstr_new_buffer") {
        str_buffer_t buffer1 = nstr_new_buffer("test1", stdalloc);
        IS_TRUE(buffer1.is_valid, "Validity of c string buffer");
        nstr_destroy_buffer(&buffer1);

        str_buffer_t buffer2 = nstr_new_buffer(nstr_to_str("test2"), stdalloc);
        IS_TRUE(buffer2.is_valid, "Validity of string buffer");
        nstr_destroy_buffer(&buffer2);
    }



    RESULT();
}
