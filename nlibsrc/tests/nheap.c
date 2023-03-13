#include "nlib/nheap.h"
#include "nlib/stdalloc.h"
#include "nlib/test.h"

int main() {
    TEST_SUITE("stdalloc_wrapper") {
        char* test_alloc = (char*) stdalloc.proc(&stdalloc, 10, NULL);
        IS_TRUE(test_alloc, "Allocation returns pointer");
        test_alloc[3] = 55;
        IS_EQUAL(test_alloc[3], 55, "Editing of memory area succedes");
        stdalloc.proc(&stdalloc, 0, test_alloc);

    }

}
