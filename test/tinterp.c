/*
 * tinterp.c
 *
 * Test suite for interpolation functions
 */

#include <stdio.h>

#include "..\include\interp.h"
#include "..\include\trig.h"
#include "tmath.h"

/* Test linear interpolation */
void test_linear_interp(void) {
    fixed_t a, b, t, result;

    /* Test basic interpolation */
    a = fixed_from_int(10);
    b = fixed_from_int(20);
    t = fixed_from_float(0.5f);
    result = linear_interp(a, b, t);

    TEST_ASSERT_EQUAL_FLOAT(15.0f, fixed_to_float(result), 0.01f);

    /* Test t = 0 */
    t = FIXED_ZERO;
    result = linear_interp(a, b, t);

    TEST_ASSERT_EQUAL_FLOAT(10.0f, fixed_to_float(result), 0.01f);

    /* Test t = 1 */
    t = FIXED_ONE;
    result = linear_interp(a, b, t);

    TEST_ASSERT_EQUAL_FLOAT(20.0f, fixed_to_float(result), 0.01f);

    /* Test with t out of range */
    t = fixed_from_float(1.5f);
    result = linear_interp(a, b, t);

    TEST_ASSERT_EQUAL_FLOAT(20.0f, fixed_to_float(result), 0.01f);

    t = fixed_from_float(-0.5f);
    result = linear_interp(a, b, t);

    TEST_ASSERT_EQUAL_FLOAT(10.0f, fixed_to_float(result), 0.01f);

    /* Test with negative values */
    a = fixed_from_int(-10);
    b = fixed_from_int(10);
    t = fixed_from_float(0.5f);
    result = linear_interp(a, b, t);

    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(result), 0.01f);
}

int main(void) {
    test_results_t results;

    /* Initialize the test framework */
    test_init(&results);

    /* Run interpolation tests */
    test_begin_suite(&results, "Basic Interpolation");
    test_run(&results, test_linear_interp, "Linear Interpolation");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
