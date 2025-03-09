/*
 * tmatrix.c
 *
 * Test suite for matrix operations
 */

#include <stdio.h>

#include "..\include\matrix.h"
#include "..\include\trig.h"
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

/* Test matrix scalar multiplication */
void test_matrix_scale(void) {
    matrix_t m = matrix_init();
    matrix_t result;
    fixed_t scalar;
    int row, col;

    /* Initialize test matrix */
    matrix_set(&m, 0, 0, fixed_from_int(1));
    matrix_set(&m, 1, 1, fixed_from_int(2));
    matrix_set(&m, 2, 2, fixed_from_int(3));
    matrix_set(&m, 3, 3, fixed_from_int(4));
    matrix_set(&m, 0, 3, fixed_from_int(5));
    matrix_set(&m, 1, 2, fixed_from_int(-2));

    scalar = fixed_from_int(2);
    result = matrix_scale(&m, scalar);

    /* Check results */
    TEST_ASSERT_EQUAL_INT(2, fixed_to_int(result.m[0][0]));
    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(result.m[1][1]));
    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(result.m[2][2]));
    TEST_ASSERT_EQUAL_INT(8, fixed_to_int(result.m[3][3]));
    TEST_ASSERT_EQUAL_INT(10, fixed_to_int(result.m[0][3]));
    TEST_ASSERT_EQUAL_INT(-4, fixed_to_int(result.m[1][2]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.m[2][1]));

    scalar = fixed_from_float(0.5f);
    result = matrix_scale(&m, scalar);

    /* Check results */
    TEST_ASSERT_EQUAL_FLOAT(0.5f, fixed_to_float(result.m[0][0]), 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(result.m[1][1]), 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(1.5f, fixed_to_float(result.m[2][2]), 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, fixed_to_float(result.m[3][3]), 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(2.5f, fixed_to_float(result.m[0][3]), 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, fixed_to_float(result.m[1][2]), 0.001f);

    scalar = FIXED_ZERO;
    result = matrix_scale(&m, scalar);

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.m[row][col]));
        }
    }

    scalar = fixed_from_int(-1);
    result = matrix_scale(&m, scalar);

    /* Check results */
    TEST_ASSERT_EQUAL_INT(-1, fixed_to_int(result.m[0][0]));
    TEST_ASSERT_EQUAL_INT(-2, fixed_to_int(result.m[1][1]));
    TEST_ASSERT_EQUAL_INT(-3, fixed_to_int(result.m[2][2]));
    TEST_ASSERT_EQUAL_INT(-4, fixed_to_int(result.m[3][3]));
    TEST_ASSERT_EQUAL_INT(-5, fixed_to_int(result.m[0][3]));
    TEST_ASSERT_EQUAL_INT(2, fixed_to_int(result.m[1][2]));
}

/* Test matrix-vector multiplication with 4D vector */
void test_matrix_mul_vector4(void) {
    matrix_t m = matrix_init();
    vector4_t v;
    vector4_t result;

    /* Test with identity matrix */
    m = matrix_identity();
    v = vector4_init_int(2, 3, 4, 1);

    result = matrix_mul_vector4(&m, &v);

    /* Identity matrix should not change the vector */
    TEST_ASSERT_EQUAL_INT(2, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(3, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(result.z));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.w));

    /* Test with non-identity matrix */
    m = matrix_init();
    matrix_set(&m, 0, 0, fixed_from_int(2));  // Scale x by 2
    matrix_set(&m, 1, 1, fixed_from_int(3));  // Scale y by 3
    matrix_set(&m, 2, 2, fixed_from_int(4));  // Scale z by 4
    matrix_set(&m, 3, 3, fixed_from_int(1));  // Scale w by 1

    result = matrix_mul_vector4(&m, &v);

    /* Should scale each component */
    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(9, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(16, fixed_to_int(result.z));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.w));

    /* Test translation using a 4D vector */
    m = matrix_identity();
    matrix_set(&m, 0, 3, fixed_from_int(10));  // Translate x by 10
    matrix_set(&m, 1, 3, fixed_from_int(20));  // Translate y by 20
    matrix_set(&m, 2, 3, fixed_from_int(30));  // Translate z by 30

    v = vector4_init_int(5, 6, 7, 1);

    result = matrix_mul_vector4(&m, &v);

    /* Should translate the point */
    TEST_ASSERT_EQUAL_INT(15, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(26, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(37, fixed_to_int(result.z));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.w));

    /* Test that direction vectors are not affected by translation */
    v = vector4_init_int(5, 6, 7, 0);

    result = matrix_mul_vector4(&m, &v);

    /* Should translate the point */
    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(7, fixed_to_int(result.z));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.w));
}

/* Test matrix-vector multiplication with 3D vector */
void test_matrix_mul_vector3(void) {
    matrix_t m = matrix_init();
    vector3_t v;
    vector3_t result;

    /* Test with identity matrix */
    m = matrix_identity();
    v = vector3_init_int(2, 3, 4);

    result = matrix_mul_vector3(&m, &v);

    /* Identity matrix should not change the vector */
    TEST_ASSERT_EQUAL_INT(2, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(3, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(result.z));

    /* Test with non-identity matrix */
    m = matrix_init();
    matrix_set(&m, 0, 0, fixed_from_int(2));  // Scale x by 2
    matrix_set(&m, 1, 1, fixed_from_int(3));  // Scale y by 3
    matrix_set(&m, 2, 2, fixed_from_int(4));  // Scale z by 4
    matrix_set(&m, 3, 3, fixed_from_int(1));  // Scale w by 1

    result = matrix_mul_vector3(&m, &v);

    /* Should scale each component */
    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(9, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(16, fixed_to_int(result.z));

    /* Test translation using a 3D vector */
    m = matrix_identity();
    matrix_set(&m, 0, 3, fixed_from_int(10));  // Translate x by 10
    matrix_set(&m, 1, 3, fixed_from_int(20));  // Translate y by 20
    matrix_set(&m, 2, 3, fixed_from_int(30));  // Translate z by 30

    v = vector3_init_int(5, 6, 7);

    result = matrix_mul_vector3(&m, &v);

    /* Should translate the point */
    TEST_ASSERT_EQUAL_INT(15, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(26, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(37, fixed_to_int(result.z));
}

/* Test matrix-matrix multiplication */
void test_matrix_multiplication(void) {
    matrix_t a = matrix_init();
    matrix_t b = matrix_init();
    matrix_t result, ab, ba;

    /* Initialize test matrix a */
    matrix_set(&a, 0, 0, fixed_from_int(1));
    matrix_set(&a, 0, 1, fixed_from_int(2));
    matrix_set(&a, 1, 0, fixed_from_int(3));
    matrix_set(&a, 1, 1, fixed_from_int(4));
    matrix_set(&a, 2, 2, fixed_from_int(1));
    matrix_set(&a, 3, 3, fixed_from_int(1));

    /* Initialize test matrix b */
    matrix_set(&b, 0, 0, fixed_from_int(2));
    matrix_set(&b, 0, 1, fixed_from_int(0));
    matrix_set(&b, 1, 0, fixed_from_int(1));
    matrix_set(&b, 1, 1, fixed_from_int(3));
    matrix_set(&b, 2, 2, fixed_from_int(4));
    matrix_set(&b, 3, 3, fixed_from_int(1));

    result = matrix_mul(&a, &b);

    /* Check results */
    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(result.m[0][0]));
    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(result.m[0][1]));
    TEST_ASSERT_EQUAL_INT(10, fixed_to_int(result.m[1][0]));
    TEST_ASSERT_EQUAL_INT(12, fixed_to_int(result.m[1][1]));
    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(result.m[2][2]));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.m[3][3]));

    /* Check that other elements are 0 */
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.m[0][2]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.m[0][3]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.m[1][2]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.m[1][3]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.m[2][0]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.m[2][1]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.m[2][3]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.m[3][0]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.m[3][1]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.m[3][2]));

    /* Test multiplication with identity matrix */
    b = matrix_identity();
    result = matrix_mul(&a, &b);

    /* a * I = a */
    TEST_ASSERT("Multiply by identity preserves matrix", matrix_equals(&result, &a));

    /* Test multiplication order */
    a = matrix_init();
    b = matrix_init();

    /* Create simple non-commutative matrices */
    matrix_set(&a, 0, 0, fixed_from_int(1));
    matrix_set(&a, 0, 1, fixed_from_int(2));
    matrix_set(&a, 1, 0, fixed_from_int(3));
    matrix_set(&a, 1, 1, fixed_from_int(4));

    matrix_set(&b, 0, 0, fixed_from_int(5));
    matrix_set(&b, 0, 1, fixed_from_int(6));
    matrix_set(&b, 1, 0, fixed_from_int(7));
    matrix_set(&b, 1, 1, fixed_from_int(8));

    ab = matrix_mul(&a, &b);
    ba = matrix_mul(&b, &a);

    /* Should not be equal */
    TEST_ASSERT("Matrix multiplication not commutative", !matrix_equals(&ab, &ba));

    /* Verify specific values in ab */
    TEST_ASSERT_EQUAL_INT(19, fixed_to_int(ab.m[0][0]));
    TEST_ASSERT_EQUAL_INT(22, fixed_to_int(ab.m[0][1]));
    TEST_ASSERT_EQUAL_INT(43, fixed_to_int(ab.m[1][0]));
    TEST_ASSERT_EQUAL_INT(50, fixed_to_int(ab.m[1][1]));

    /* Verify specific values in ba */
    TEST_ASSERT_EQUAL_INT(23, fixed_to_int(ba.m[0][0]));
    TEST_ASSERT_EQUAL_INT(34, fixed_to_int(ba.m[0][1]));
    TEST_ASSERT_EQUAL_INT(31, fixed_to_int(ba.m[1][0]));
    TEST_ASSERT_EQUAL_INT(46, fixed_to_int(ba.m[1][1]));
}

/* Test matrix translation creation */
void test_matrix_translation(void) {
    fixed_t x = fixed_from_int(5);
    fixed_t y = fixed_from_int(-3);
    fixed_t z = fixed_from_int(7);
    matrix_t trans = matrix_translation(x, y, z);
    matrix_t trans2, combined;
    vector4_t point, result, dir;

    /* Check that it's the identity with translation values */
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(trans.m[0][0]));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(trans.m[1][1]));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(trans.m[2][2]));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(trans.m[3][3]));

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(trans.m[0][1]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(trans.m[0][2]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(trans.m[1][0]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(trans.m[1][2]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(trans.m[2][0]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(trans.m[2][1]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(trans.m[3][0]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(trans.m[3][1]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(trans.m[3][2]));

    /* Check translation components */
    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(trans.m[0][3]));
    TEST_ASSERT_EQUAL_INT(-3, fixed_to_int(trans.m[1][3]));
    TEST_ASSERT_EQUAL_INT(7, fixed_to_int(trans.m[2][3]));

    /* Test translating a point */
    point = vector4_init_int(2, 3, 4, 1);
    result = matrix_mul_vector4(&trans, &point);

    /* Should be translated */
    TEST_ASSERT_EQUAL_INT(7, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(11, fixed_to_int(result.z));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.w));

    /* Test with a direction vector (should not change) */
    dir = vector4_init_int(2, 3, 4, 0);
    result = matrix_mul_vector4(&trans, &dir);

    /* Direction should be unchanged */
    TEST_ASSERT_EQUAL_INT(2, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(3, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(result.z));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.w));

    /* Test that consecutive translations add up */
    trans2 = matrix_translation(fixed_from_int(10), fixed_from_int(20), fixed_from_int(30));
    combined = matrix_mul(&trans2, &trans);

    TEST_ASSERT_EQUAL_INT(15, fixed_to_int(combined.m[0][3]));
    TEST_ASSERT_EQUAL_INT(17, fixed_to_int(combined.m[1][3]));
    TEST_ASSERT_EQUAL_INT(37, fixed_to_int(combined.m[2][3]));
}

/* Test scaling matrix creation */
void test_matrix_scaling(void) {
    fixed_t x = fixed_from_int(2);
    fixed_t y = fixed_from_int(3);
    fixed_t z = fixed_from_int(4);
    matrix_t scale = matrix_scaling(x, y, z);
    matrix_t scale2, combined, uniform;
    vector4_t point, result, dir;

    /* Check the scale matrix structure */
    TEST_ASSERT_EQUAL_INT(2, fixed_to_int(scale.m[0][0]));
    TEST_ASSERT_EQUAL_INT(3, fixed_to_int(scale.m[1][1]));
    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(scale.m[2][2]));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(scale.m[3][3]));

    /* All other elements should be zero */
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(scale.m[0][1]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(scale.m[0][2]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(scale.m[0][3]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(scale.m[1][0]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(scale.m[1][2]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(scale.m[1][3]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(scale.m[2][0]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(scale.m[2][1]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(scale.m[2][3]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(scale.m[3][0]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(scale.m[3][1]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(scale.m[3][2]));

    /* Test scaling a point */
    point = vector4_init_int(5, 10, 15, 1);
    result = matrix_mul_vector4(&scale, &point);

    /* Should be scaled */
    TEST_ASSERT_EQUAL_INT(10, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(30, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(60, fixed_to_int(result.z));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.w));

    /* Test scaling a direction vector */
    dir = vector4_init_int(5, 10, 15, 0);
    result = matrix_mul_vector4(&scale, &dir);

    /* Direction should be scaled */
    TEST_ASSERT_EQUAL_INT(10, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(30, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(60, fixed_to_int(result.z));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.w));

    /* Test that consecutive scaling multiplies */
    scale2 = matrix_scaling(fixed_from_int(3), fixed_from_int(2), fixed_from_int(5));
    combined = matrix_mul(&scale2, &scale);

    /* Check combined scale factors */
    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(combined.m[0][0]));
    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(combined.m[1][1]));
    TEST_ASSERT_EQUAL_INT(20, fixed_to_int(combined.m[2][2]));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(combined.m[3][3]));

    /* Test uniform scaling (same factor for all axes) */
    uniform = matrix_scaling(fixed_from_int(2), fixed_from_int(2), fixed_from_int(2));
    point = vector4_init_int(3, 4, 5, 1);
    result = matrix_mul_vector4(&uniform, &point);

    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(8, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(10, fixed_to_int(result.z));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.w));
}

/* Test rotation matrix creation for X axis */
void test_matrix_rotation_x(void) {
    unsigned char angle = 64;  // 90 deg
    matrix_t rot;
    vector4_t v = vector4_init_int(1, 1, 1, 1);
    vector4_t result;

    /* Initialize the table */
    trig_init();

    rot = matrix_rotation_x(angle);

    /* Check the matrix structure */
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(rot.m[0][0]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[0][1]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[0][2]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[0][3]));

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[1][0]));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(rot.m[1][1]), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, fixed_to_float(rot.m[1][2]), 0.01f);
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[1][3]));

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[2][0]));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(rot.m[2][1]), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(rot.m[2][2]), 0.01f);
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[2][3]));

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[3][0]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[3][1]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[3][2]));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(rot.m[3][3]));

    /* Test rotating a point (1, 1, 1, 1) by 90 degrees around X */
    result = matrix_mul_vector4(&rot, &v);

    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, fixed_to_float(result.y), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(result.z), 0.01f);
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.w));
}

/* Test rotation matrix creation for Y axis */
void test_matrix_rotation_y(void) {
    unsigned char angle = 64;  // 90 deg
    matrix_t rot;
    vector4_t v = vector4_init_int(1, 1, 1, 1);
    vector4_t result;

    /* Initialize the table */
    trig_init();

    rot = matrix_rotation_y(angle);

    /* Check the matrix structure */
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(rot.m[0][0]), 0.01f);
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[0][1]));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(rot.m[0][2]), 0.01f);
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[0][3]));

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[1][0]));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(rot.m[1][1]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[1][2]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[1][3]));

    TEST_ASSERT_EQUAL_FLOAT(-1.0f, fixed_to_float(rot.m[2][0]), 0.01f);
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[2][1]));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(rot.m[2][2]), 0.01f);
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[2][3]));

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[3][0]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[3][1]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[3][2]));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(rot.m[3][3]));

    /* Test rotating a point (1, 1, 1, 1) by 90 degrees around Y */
    result = matrix_mul_vector4(&rot, &v);

    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(result.x), 0.01f);
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, fixed_to_float(result.z), 0.01f);
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.w));
}

/* Test rotation matrix creation for Z axis */
void test_matrix_rotation_z(void) {
    unsigned char angle = 64;  // 90 deg
    matrix_t rot;
    vector4_t v = vector4_init_int(1, 1, 1, 1);
    vector4_t result;

    /* Initialize the table */
    trig_init();

    rot = matrix_rotation_z(angle);

    /* Check the matrix structure */
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(rot.m[0][0]), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, fixed_to_float(rot.m[0][1]), 0.01f);
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[0][2]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[0][3]));

    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(rot.m[1][0]), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(rot.m[1][1]), 0.01f);
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[1][2]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[1][3]));

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[2][0]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[2][1]));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(rot.m[2][2]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[2][3]));

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[3][0]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[3][1]));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(rot.m[3][2]));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(rot.m[3][3]));

    /* Test rotating a point (1, 1, 1, 1) by 90 degrees around Z */
    result = matrix_mul_vector4(&rot, &v);

    TEST_ASSERT_EQUAL_FLOAT(-1.0f, fixed_to_float(result.x), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(result.y), 0.01f);
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.z));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.w));
}

/* Test multiple transformations applied in sequence */
void test_combined_transformations(void) {
    vector4_t point = vector4_init_int(10, 5, 3, 1);
    vector4_t result;
    matrix_t scale, rot_x, rot_y, rot_z, trans, combined;

    /* Initialize the table */
    trig_init();

    /* Create individual transformation matrices */
    scale = matrix_scaling(fixed_from_int(2), fixed_from_int(2), fixed_from_int(2));
    rot_x = matrix_rotation_x(32);  // 45 deg
    rot_y = matrix_rotation_y(32);  // 45 deg
    rot_z = matrix_rotation_z(32);  // 45 deg
    trans = matrix_translation(fixed_from_int(5), fixed_from_int(-3), fixed_from_int(10));

    /* Combine transformations in correct order */
    combined = matrix_identity();
    combined = matrix_mul(&combined, &scale);
    combined = matrix_mul(&combined, &rot_x);
    combined = matrix_mul(&combined, &rot_y);
    combined = matrix_mul(&combined, &rot_z);
    combined = matrix_mul(&combined, &trans);

    /* Apply the combined transformation to the point */
    result = matrix_mul_vector4(&combined, &point);

    /* Verify results of combined transformation */
    TEST_ASSERT_EQUAL_FLOAT(31.38f, fixed_to_float(result.x), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(13.19f, fixed_to_float(result.y), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(20.80f, fixed_to_float(result.z), 0.01f);
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.w));
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
    test_run(&results, test_matrix_scale, "Scalar Multiplication");
    test_run(&results, test_matrix_multiplication, "Matrix-Matrix Multiplication");
    test_end_suite(&results);

    /* Run matrix-vector multiplication tests */
    test_begin_suite(&results, "Matrix-Vector Operations");
    test_run(&results, test_matrix_mul_vector4, "Matrix-Vector4 Multiplication");
    test_run(&results, test_matrix_mul_vector3, "Matrix-Vector3 Multiplication");
    test_end_suite(&results);

    /* Run matrix transform matrices tests */
    test_begin_suite(&results, "Transform Matrices");
    test_run(&results, test_matrix_translation, "Translation Matrix");
    test_run(&results, test_matrix_scaling, "Scaling Matrix");
    test_run(&results, test_matrix_rotation_x, "X-Axis Rotation Matrix");
    test_run(&results, test_matrix_rotation_y, "Y-Axis Rotation Matrix");
    test_run(&results, test_matrix_rotation_z, "Z-Axis Rotation Matrix");
    test_run(&results, test_combined_transformations, "Combined Sequential Transformations");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
