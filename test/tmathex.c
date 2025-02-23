/*
 * tmathex.c
 *
 * Example usage of the math testing framework
 */

#include <stdio.h>

#include "tmath.h"

void test_basic_assertion(void) {
    TEST_ASSERT("True", 1 == 1);
}

/* Sample test functions */
void test_basic_addition(void) {
    TEST_ASSERT_EQUAL_INT(4, 2 + 2);
}

void test_basic_multiplication(void) {
    TEST_ASSERT_EQUAL_INT(6, 2 * 3);
}

void test_float_operations(void) {
    TEST_ASSERT_EQUAL_FLOAT(0.5f, 1.0f / 2.0f, 0.001f);
}

int main(void) {
    test_results_t results;

    /* Initialize the test framework */
    test_init(&results);

    /* Run basic tests */
    test_begin_suite(&results, "Basic Tests");
    test_run(&results, test_basic_assertion, "True Assertion");
    test_run(&results, test_basic_addition, "Integer Addition");
    test_run(&results, test_basic_multiplication, "Integer Multiplication");
    test_run(&results, test_float_operations, "Float Operations");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
