#include <stdbool.h>

#include "nlib/nstack.h"
#include "nlib/stdalloc.h"
#include "nlib/test.h"

int main() {
    TEST_SUITE("stack type creation") {
        stack_t(int) test_stack;
        nstk_setup(test_stack, 5, stdalloc);
        IS_EQUAL(test_stack.frame.size, 5, "stack has correct size");

        nstk_destroy(test_stack);
    }

    TEST_SUITE("nstk_push") {
        stack_t(int) test_stack;
        bool push_result;

        nstk_setup(test_stack, 2, stdalloc);

        push_result = nstk_push(test_stack, 1);
        IS_TRUE(push_result, "Empty stack with valid size can be pushed to");

        push_result = nstk_push(test_stack, 4);
        IS_TRUE(push_result, "Non-Empty stack with valid size can be pushed to");

        push_result = nstk_push(test_stack, 3);
        IS_TRUE(!push_result, "Full stack with valid size can not be pushed to");

        nstk_destroy(test_stack);
    }

    TEST_SUITE("nstk_size") {
        stack_t(double) test_stack;

        nstk_setup(test_stack, 2, stdalloc);
        IS_EQUAL(nstk_size(test_stack), 0, "new stack is empty");

        nstk_push(test_stack, 6.9);
        IS_EQUAL(nstk_size(test_stack), 1, "stack pushed to once has correct size");

        nstk_push(test_stack, 6.9);
        nstk_push(test_stack, 6.9);
        IS_EQUAL(nstk_size(test_stack), 2, "stacksize does not exceed maximum caoacity");

        nstk_destroy(test_stack);
    }

    TEST_SUITE("nstk_top") {
        stack_t(long) test_stack;

        nstk_setup(test_stack, 2, stdalloc);
        nstk_push(test_stack, 50);

        IS_EQUAL(nstk_top(test_stack), 50, "top element is correct");
        
        nstk_push(test_stack, 60);
        IS_EQUAL(nstk_top(test_stack), 60, "top element changes");

        nstk_destroy(test_stack);
    }

    TEST_SUITE("nstk_pop") {
        stack_t(char) test_stack;

        nstk_setup(test_stack, 2, stdalloc);
        nstk_push(test_stack, 'b');
        nstk_push(test_stack, 'v');

        IS_EQUAL(nstk_size(test_stack), 2, "stack size is correct before pop");

        nstk_pop(test_stack);
        IS_EQUAL(nstk_size(test_stack), 1, "stack size is correct after pop");

        nstk_destroy(test_stack);
    }

    RESULT();
}
