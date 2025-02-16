/*
 * fixed_test.c
 *
 * Test suite for fixed-point number system
 */

#include <stdio.h>

#include "..\include\fixed.h"
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

/* Test addition of positive numbers */
int test_addition_positive(void) {
    fixed_t a = fixed_from_int(5);
    fixed_t b = fixed_from_int(3);
    fixed_t result = fixed_add(a, b);

    TEST_ASSERT_EQUAL_INT(8, fixed_to_int(result));
}

/* Test addition with fractional components */
int test_addition_fractional(void) {
    fixed_t a = fixed_from_float(3.5f);
    fixed_t b = fixed_from_float(2.25f);
    fixed_t result = fixed_add(a, b);

    TEST_ASSERT_EQUAL_FLOAT(5.75f, fixed_to_float(result), 0.0001f);
}

/* Test subtraction of positive numbers */
int test_subtraction_positive(void) {
    fixed_t a = fixed_from_int(5);
    fixed_t b = fixed_from_int(3);
    fixed_t result = fixed_sub(a, b);

    TEST_ASSERT_EQUAL_INT(2, fixed_to_int(result));
}

/* Test subtraction with negative result */
int test_subtraction_negative_result(void) {
    fixed_t a = fixed_from_int(3);
    fixed_t b = fixed_from_int(5);
    fixed_t result = fixed_sub(a, b);

    TEST_ASSERT_EQUAL_INT(-2, fixed_to_int(result));
}

/* Test subtraction with fractional components */
int test_subtraction_fractional(void) {
    fixed_t a = fixed_from_float(5.5f);
    fixed_t b = fixed_from_float(2.25f);
    fixed_t result = fixed_sub(a, b);

    TEST_ASSERT_EQUAL_FLOAT(3.25f, fixed_to_float(result), 0.0001f);
}

int main(void) {
    test_results_t results;

    /* Initialize the test framework */
    test_init(&results);

    /* Run conversion tests */
    test_begin_suite(&results, "Fixed-Point Conversion");
    test_run(&results, test_int_conversion, "Integer Conversion");
    test_run(&results, test_zero, "Zero Conversion");
    test_run(&results, test_negative, "Negative Conversion");
    test_run(&results, test_float_conversion, "Float Conversion");
    test_run(&results, test_negative_float, "Negative Float");
    test_end_suite(&results);

    /* Run arithmetic tests */
    test_begin_suite(&results, "Fixed-Point Arithmetic");
    test_run(&results, test_addition_positive, "Addition of Positive Integers");
    test_run(&results, test_addition_fractional, "Addition with Fractions");
    test_run(&results, test_subtraction_positive, "Subtraction of Positive Integers");
    test_run(&results, test_subtraction_negative_result, "Subtraction with Negative Result");
    test_run(&results, test_subtraction_fractional, "Subtraction with Fractions");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
