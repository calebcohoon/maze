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

/* Test matrix addition */
void test_matrix_add(void) {
    matrix_t a = matrix_init();
    matrix_t b = matrix_init();
    matrix_t result;

    /* Initialize test matrices */
    matrix_set(&a, 0, 0, fixed_from_int(1));
    matrix_set(&a, 1, 1, fixed_from_int(2));
    matrix_set(&a, 2, 2, fixed_from_int(3));
    matrix_set(&a, 3, 3, fixed_from_int(4));

    matrix_set(&b, 0, 0, fixed_from_int(5));
    matrix_set(&b, 1, 1, fixed_from_int(6));
    matrix_set(&b, 2, 2, fixed_from_int(7));
    matrix_set(&b, 3, 3, fixed_from_int(8));
    matrix_set(&b, 0, 3, fixed_from_int(9));

    result = matrix_add(&a, &b);

    /* Check results */
    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(result.m[0][0]));
    TEST_ASSERT_EQUAL_INT(8, fixed_to_int(result.m[1][1]));
    TEST_ASSERT_EQUAL_INT(10, fixed_to_int(result.m[2][2]));
    TEST_ASSERT_EQUAL_INT(12, fixed_to_int(result.m[3][3]));
    TEST_ASSERT_EQUAL_INT(9, fixed_to_int(result.m[0][3]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.m[1][2]));
}

/* Test matrix subtraction */
void test_matrix_sub(void) {
    matrix_t a = matrix_init();
    matrix_t b = matrix_init();
    matrix_t result;

    /* Initialize test matrices */
    matrix_set(&a, 0, 0, fixed_from_int(10));
    matrix_set(&a, 1, 1, fixed_from_int(15));
    matrix_set(&a, 2, 2, fixed_from_int(20));
    matrix_set(&a, 3, 3, fixed_from_int(25));
    matrix_set(&a, 1, 3, fixed_from_int(12));

    matrix_set(&b, 0, 0, fixed_from_int(5));
    matrix_set(&b, 1, 1, fixed_from_int(7));
    matrix_set(&b, 2, 2, fixed_from_int(9));
    matrix_set(&b, 3, 3, fixed_from_int(11));

    result = matrix_sub(&a, &b);

    /* Check results */
    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result.m[0][0]));
    TEST_ASSERT_EQUAL_INT(8, fixed_to_int(result.m[1][1]));
    TEST_ASSERT_EQUAL_INT(11, fixed_to_int(result.m[2][2]));
    TEST_ASSERT_EQUAL_INT(14, fixed_to_int(result.m[3][3]));
    TEST_ASSERT_EQUAL_INT(12, fixed_to_int(result.m[1][3]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.m[3][0]));
}

/* Test addition and subtraction with identity matrix */
void test_matrix_add_sub_identity(void) {
    matrix_t a = matrix_init();
    matrix_t identity = matrix_identity();
    matrix_t result;

    /* Initialize test matrix */
    matrix_set(&a, 0, 0, fixed_from_int(1));
    matrix_set(&a, 1, 1, fixed_from_int(2));
    matrix_set(&a, 2, 2, fixed_from_int(3));
    matrix_set(&a, 3, 3, fixed_from_int(4));
    matrix_set(&a, 0, 2, fixed_from_int(5));

    result = matrix_add(&a, &identity);

    /* Check results */
    TEST_ASSERT_EQUAL_INT(2, fixed_to_int(result.m[0][0]));
    TEST_ASSERT_EQUAL_INT(3, fixed_to_int(result.m[1][1]));
    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(result.m[2][2]));
    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result.m[3][3]));
    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result.m[0][2]));

    result = matrix_sub(&a, &identity);

    /* Check results */
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.m[0][0]));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.m[1][1]));
    TEST_ASSERT_EQUAL_INT(2, fixed_to_int(result.m[2][2]));
    TEST_ASSERT_EQUAL_INT(3, fixed_to_int(result.m[3][3]));
    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result.m[0][2]));
}

int main(void) {
    test_results_t results;

    /* Initialize the test framework */
    test_init(&results);

    /* Run matrix initialization tests */
    test_begin_suite(&results, "Matrix Initialization");
    test_run(&results, test_matrix_init, "Zero Matrix Initialization");
    test_run(&results, test_matrix_identity, "Identity Matrix Creation");
    test_end_suite(&results);

    /* Run matrix element access tests */
    test_begin_suite(&results, "Matrix Element Access");
    test_run(&results, test_matrix_get_set, "Set and Get Elements");
    test_run(&results, test_matrix_bounds, "Bounds Checking");
    test_end_suite(&results);

    /* Run matrix validation tests */
    test_begin_suite(&results, "Matrix Validation");
    test_run(&results, test_matrix_is_identity, "Identity Matrix Check");
    test_run(&results, test_matrix_equals, "Matrix Equality Check");
    test_end_suite(&results);

    /* Run matrix operation tests */
    test_begin_suite(&results, "Matrix Basic Operations");
    test_run(&results, test_matrix_add, "Matrix Addition");
    test_run(&results, test_matrix_sub, "Matrix Subtraction");
    test_run(&results, test_matrix_add_sub_identity, "Add/Sub with Identity");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
