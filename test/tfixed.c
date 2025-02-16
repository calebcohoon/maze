/*
 * fixed_test.c
 *
 * Test suite for fixed-point number system
 */

#include "..\include\fixed.h"

#include <stdio.h>

#include "tmath.h"

/* Test integer conversion */
int test_int_conversion(void) {
    int original = 42;
    fixed_t fixed = fixed_from_int(original);
    int result = fixed_to_int(fixed);

    TEST_ASSERT_EQUAL_INT(original, result);
}

/* Test zero conversion */
int test_zero(void) {
    fixed_t fixed = fixed_from_int(0);

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(fixed));
}

/* Test negative conversion */
int test_negative(void) {
    int original = -42;
    fixed_t fixed = fixed_from_int(original);
    int result = fixed_to_int(fixed);

    TEST_ASSERT_EQUAL_INT(original, result);
}

/* Test float conversion (approximate) */
int test_float_conversion(void) {
    float original = 3.14159f;
    fixed_t fixed = fixed_from_float(original);
    float result = fixed_to_float(fixed);

    TEST_ASSERT_EQUAL_FLOAT(original, result, 0.0001f);
}

/* Test float conversion with negative numbers */
int test_negative_float(void) {
    float original = -3.14159f;
    fixed_t fixed = fixed_from_float(original);
    float result = fixed_to_float(fixed);

    TEST_ASSERT_EQUAL_FLOAT(original, result, 0.0001f);
}

int main(void) {
    test_results_t results;

    /* Initialize the test framework */
    test_init(&results);

    /* Run basic assertion test */
    test_begin_suite(&results, "Fixed-Point Conversion");
    test_run(&results, test_int_conversion, "Integer Conversion");
    test_run(&results, test_zero, "Zero Conversion");
    test_run(&results, test_negative, "Negative Conversion");
    test_run(&results, test_float_conversion, "Float Conversion");
    test_run(&results, test_negative_float, "Negative Float");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
