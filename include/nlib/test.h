#include <stdio.h>

int G_amount_of_tests = 0;
int G_passed_tests = 0;

#define TEST_SUITE(name) \
    printf("Testsuite \"%s\"\n", name);\
    for(int _testsuite_index_ = 0, _tests_conducted_ = 0, _tests_passed_ = 0; \
        _testsuite_index_++ < 1; \
        printf("  -Tests conducted: %d, of which %d passed\n\n", _tests_conducted_, _tests_passed_))

#define IS_EQUAL(test, value, name)\
    _tests_conducted_++; \
    G_amount_of_tests++; \
    if (test == value) { \
        _tests_passed_++; \
        G_passed_tests++; \
        printf("  [OK]Test: [%s] passed\n", name); \
    } else \
        printf( \
            "  [FAIL]Test: [%s] failed, valued is %lld but should be %lld\n", \
            name,  \
            (long long int) test, \
            (long long int) value);

#define IS_TRUE(test, name) \
    _tests_conducted_++; \
    G_amount_of_tests++; \
    if(test) { \
        _tests_passed_++; \
        G_passed_tests++; \
        printf("  [OK]Test: [%s] passed\n", name); \
    } else \
        printf("  [FAIL]Test: [%s] failed, value is false\n", name);

#define RESULT() printf("------------\nTotal tests conducted: %d, Total tests passed: %d.\n", G_amount_of_tests, G_passed_tests)
