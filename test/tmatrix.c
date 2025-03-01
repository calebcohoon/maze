/*
 * tmatrix.c
 *
 * Test suite for matrix operations
 */

#include <stdio.h>

#include "..\include\matrix.h"
#include "tmath.h"

/* Test matrix initialization to zero */
void test_matrix_init(void) {
    matrix_t m = matrix_init();
    int row, col;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            TEST_ASSERT_EQUAL_INT(0, fixed_to_int(m.m[row][col]));
        }
    }
}

/* Test identity matrix creation */
void test_matrix_identity(void) {
    matrix_t m = matrix_identity();
    int row, col;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            if (row == col) {
                TEST_ASSERT_EQUAL_INT(1, fixed_to_int(m.m[row][col]));
            } else {
                TEST_ASSERT_EQUAL_INT(0, fixed_to_int(m.m[row][col]));
            }
        }
    }
}

/* Test setting and getting matrix elements */
void test_matrix_get_set(void) {
    matrix_t m = matrix_init();

    /* Set elements */
    matrix_set(&m, 0, 0, fixed_from_int(5));
    matrix_set(&m, 1, 2, fixed_from_int(7));
    matrix_set(&m, 3, 3, fixed_from_int(9));

    /* Check elements */
    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(matrix_get(&m, 0, 0)));
    TEST_ASSERT_EQUAL_INT(7, fixed_to_int(matrix_get(&m, 1, 2)));
    TEST_ASSERT_EQUAL_INT(9, fixed_to_int(matrix_get(&m, 3, 3)));
}

/* Test bounds checking in getter and setter */
void test_matrix_bounds(void) {
    matrix_t m = matrix_init();

    /* Set out of bounds */
    matrix_set(&m, 4, 0, fixed_from_int(5));
    matrix_set(&m, 0, 4, fixed_from_int(5));
    matrix_set(&m, -1, 0, fixed_from_int(5));

    /* Check elements */
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(matrix_get(&m, 4, 0)));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(matrix_get(&m, 0, 4)));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(matrix_get(&m, -1, 0)));
}

/* Test identity matrix check */
void test_matrix_is_identity(void) {
    matrix_t m1 = matrix_identity();
    matrix_t m2 = matrix_init();

    TEST_ASSERT("Identity matrix check", matrix_is_identity(&m1));

    /* Set elements */
    matrix_set(&m2, 0, 0, FIXED_ONE);
    matrix_set(&m2, 1, 1, FIXED_ONE);
    matrix_set(&m2, 2, 2, FIXED_ONE);
    matrix_set(&m2, 3, 3, FIXED_ONE);
    matrix_set(&m2, 1, 0, FIXED_ONE);

    TEST_ASSERT("Non-identity matrix check", !matrix_is_identity(&m2));
}

/* Test matrix equality check */
void test_matrix_equals(void) {
    matrix_t m1 = matrix_identity();
    matrix_t m2 = matrix_identity();
    matrix_t m3 = matrix_init();

    TEST_ASSERT("Equal matrices", matrix_equals(&m1, &m2));

    TEST_ASSERT("Unequal matrices", !matrix_equals(&m1, &m3));

    /* Set diagonal elements */
    matrix_set(&m3, 0, 0, FIXED_ONE);
    matrix_set(&m3, 1, 1, FIXED_ONE);
    matrix_set(&m3, 2, 2, FIXED_ONE);
    matrix_set(&m3, 3, 3, FIXED_ONE);

    TEST_ASSERT("Modified matrices equality", matrix_equals(&m1, &m3));
}

int main(void) {
    test_results_t results;

    /* Initialize the test framework */
    test_init(&results);

    /* Run matrix tests */
    test_begin_suite(&results, "Matrix Initialization");
    test_run(&results, test_matrix_init, "Zero Matrix Initialization");
    test_run(&results, test_matrix_identity, "Identity Matrix Creation");
    test_run(&results, test_matrix_get_set, "Set and Get Elements");
    test_run(&results, test_matrix_bounds, "Bounds Checking");
    test_run(&results, test_matrix_is_identity, "Identity Matrix Check");
    test_run(&results, test_matrix_equals, "Matrix Equality Check");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
