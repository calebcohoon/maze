/*
 * tvector.c
 *
 * Test suite for vector mathematics implementation
 */

#include <stdio.h>

#include "..\include\vector.h"
#include "tmath.h"

/* Vector2 tests */
void test_vector2_init(void) {
    vector2_t v = vector2_init(FIXED_ONE, FIXED_ONE * 2);

    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(v.x));
    TEST_ASSERT_EQUAL_INT(2, fixed_to_int(v.y));
}

void test_vector2_init_int(void) {
    vector2_t v = vector2_init_int(3, 4);

    TEST_ASSERT_EQUAL_INT(3, fixed_to_int(v.x));
    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(v.y));
}

void test_vector2_add(void) {
    vector2_t a = vector2_init_int(1, 2);
    vector2_t b = vector2_init_int(3, 4);
    vector2_t result = vector2_add(a, b);

    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(result.y));
}

void test_vector2_sub(void) {
    vector2_t a = vector2_init_int(5, 7);
    vector2_t b = vector2_init_int(2, 3);
    vector2_t result = vector2_sub(a, b);

    TEST_ASSERT_EQUAL_INT(3, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(result.y));
}

void test_vector2_scale(void) {
    vector2_t v = vector2_init_int(2, 3);
    vector2_t result = vector2_scale(v, fixed_from_int(2));

    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(result.y));
}

void test_vector2_dot(void) {
    vector2_t a = vector2_init_int(2, 3);
    vector2_t b = vector2_init_int(4, 5);
    fixed_t result = vector2_dot(a, b);

    TEST_ASSERT_EQUAL_INT(23, fixed_to_int(result));
}

/* Test 2D vector length squared */
void test_vector2_length_squared(void) {
    vector2_t v = vector2_init_int(3, 4);
    fixed_t result = vector2_length_squared(v);

    TEST_ASSERT_EQUAL_INT(25, fixed_to_int(result));
}

/* Test 2D vector length */
void test_vector2_length(void) {
    vector2_t v = vector2_init_int(3, 4);
    fixed_t result = vector2_length(v);

    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result));
}

/* Test 2D vector normalization */
void test_vector2_normalize(void) {
    vector2_t v = vector2_init_int(3, 4);
    vector2_t result = vector2_normalize(v);
    fixed_t length = vector2_length(result);

    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(length), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(0.6f, fixed_to_float(result.x), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(0.8f, fixed_to_float(result.y), 0.01f);
}

/* Vector3 tests */
void test_vector3_init(void) {
    vector3_t v = vector3_init(FIXED_ONE, FIXED_ONE * 2, FIXED_ONE * 3);

    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(v.x));
    TEST_ASSERT_EQUAL_INT(2, fixed_to_int(v.y));
    TEST_ASSERT_EQUAL_INT(3, fixed_to_int(v.z));
}

void test_vector3_init_int(void) {
    vector3_t v = vector3_init_int(4, 5, 6);

    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(v.x));
    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(v.y));
    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(v.z));
}

void test_vector3_add(void) {
    vector3_t a = vector3_init_int(1, 2, 3);
    vector3_t b = vector3_init_int(4, 5, 6);
    vector3_t result = vector3_add(a, b);

    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(7, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(9, fixed_to_int(result.z));
}

void test_vector3_sub(void) {
    vector3_t a = vector3_init_int(6, 8, 10);
    vector3_t b = vector3_init_int(1, 3, 5);
    vector3_t result = vector3_sub(a, b);

    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result.z));
}

void test_vector3_scale(void) {
    vector3_t v = vector3_init_int(2, 3, 4);
    vector3_t result = vector3_scale(v, fixed_from_int(2));

    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(8, fixed_to_int(result.z));
}

void test_vector3_dot(void) {
    vector3_t a = vector3_init_int(1, 2, 3);
    vector3_t b = vector3_init_int(4, 5, 6);
    fixed_t result = vector3_dot(a, b);

    TEST_ASSERT_EQUAL_INT(32, fixed_to_int(result));
}

void test_vector3_cross(void) {
    vector3_t a = vector3_init_int(2, 3, 4);
    vector3_t b = vector3_init_int(5, 6, 7);
    vector3_t result = vector3_cross(a, b);

    TEST_ASSERT_EQUAL_INT(-3, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(-3, fixed_to_int(result.z));
}

void test_vector3_cross_anticommutative(void) {
    vector3_t a = vector3_init_int(1, 2, 3);
    vector3_t b = vector3_init_int(4, 5, 6);
    vector3_t ab_cross = vector3_cross(a, b);
    vector3_t ba_cross = vector3_cross(b, a);

    TEST_ASSERT_EQUAL_INT(fixed_to_int(ab_cross.x), fixed_to_int(fixed_neg(ba_cross.x)));
    TEST_ASSERT_EQUAL_INT(fixed_to_int(ab_cross.y), fixed_to_int(fixed_neg(ba_cross.y)));
    TEST_ASSERT_EQUAL_INT(fixed_to_int(ab_cross.z), fixed_to_int(fixed_neg(ba_cross.z)));
}

void test_vector3_cross_basis(void) {
    vector3_t x_axis = vector3_init_int(1, 0, 0);
    vector3_t y_axis = vector3_init_int(0, 1, 0);
    vector3_t z_axis = vector3_init_int(0, 0, 1);
    vector3_t xy_cross = vector3_cross(x_axis, y_axis);
    vector3_t yz_cross = vector3_cross(y_axis, z_axis);
    vector3_t zx_cross = vector3_cross(z_axis, x_axis);

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(xy_cross.x));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(xy_cross.y));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(xy_cross.z));

    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(yz_cross.x));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(yz_cross.y));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(yz_cross.z));

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(zx_cross.x));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(zx_cross.y));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(zx_cross.z));
}

/* Test 3D vector length squared */
void test_vector3_length_squared(void) {
    vector3_t v = vector3_init_int(2, 3, 6);
    fixed_t result = vector3_length_squared(v);

    TEST_ASSERT_EQUAL_INT(49, fixed_to_int(result));
}

/* Test 3D vector length */
void test_vector3_length(void) {
    vector3_t v = vector3_init_int(3, 4, 12);
    fixed_t result = vector3_length(v);

    TEST_ASSERT_EQUAL_INT(13, fixed_to_int(result));
}

/* Test 3D vector normalization */
void test_vector3_normalize(void) {
    vector3_t v = vector3_init_int(3, 4, 12);
    vector3_t result = vector3_normalize(v);
    fixed_t length = vector3_length(result);

    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(length), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(3.0f / 13.0f, fixed_to_float(result.x), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(4.0f / 13.0f, fixed_to_float(result.y), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(12.0f / 13.0f, fixed_to_float(result.z), 0.01f);
}

/* Vector4 tests */
void test_vector4_init(void) {
    vector4_t v = vector4_init(FIXED_ONE, FIXED_ONE * 2, FIXED_ONE * 3, FIXED_ONE * 4);

    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(v.x));
    TEST_ASSERT_EQUAL_INT(2, fixed_to_int(v.y));
    TEST_ASSERT_EQUAL_INT(3, fixed_to_int(v.z));
    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(v.w));
}

void test_vector4_init_int(void) {
    vector4_t v = vector4_init_int(5, 6, 7, 8);

    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(v.x));
    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(v.y));
    TEST_ASSERT_EQUAL_INT(7, fixed_to_int(v.z));
    TEST_ASSERT_EQUAL_INT(8, fixed_to_int(v.w));
}

void test_vector4_from_vec3(void) {
    vector3_t v3 = vector3_init_int(1, 2, 3);
    vector4_t v4 = vector4_from_vec3(v3, FIXED_ONE);

    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(v4.x));
    TEST_ASSERT_EQUAL_INT(2, fixed_to_int(v4.y));
    TEST_ASSERT_EQUAL_INT(3, fixed_to_int(v4.z));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(v4.w));
}

void test_vector4_add(void) {
    vector4_t a = vector4_init_int(1, 2, 3, 4);
    vector4_t b = vector4_init_int(5, 6, 7, 8);
    vector4_t result = vector4_add(a, b);

    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(8, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(10, fixed_to_int(result.z));
    TEST_ASSERT_EQUAL_INT(12, fixed_to_int(result.w));
}

void test_vector4_sub(void) {
    vector4_t a = vector4_init_int(6, 8, 10, 11);
    vector4_t b = vector4_init_int(1, 3, 5, 6);
    vector4_t result = vector4_sub(a, b);

    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result.z));
    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result.w));
}

void test_vector4_scale(void) {
    vector4_t v = vector4_init_int(2, 3, 4, 5);
    vector4_t result = vector4_scale(v, fixed_from_int(2));

    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(result.x));
    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(result.y));
    TEST_ASSERT_EQUAL_INT(8, fixed_to_int(result.z));
    TEST_ASSERT_EQUAL_INT(10, fixed_to_int(result.w));
}

void test_vector4_dot(void) {
    vector4_t a = vector4_init_int(1, 2, 3, 4);
    vector4_t b = vector4_init_int(5, 6, 7, 8);
    fixed_t result = vector4_dot(a, b);

    TEST_ASSERT_EQUAL_INT(70, fixed_to_int(result));
}

/* Test 4D vector length squared */
void test_vector4_length_squared(void) {
    vector4_t v = vector4_init_int(1, 2, 2, 3);
    fixed_t result = vector4_length_squared(v);

    TEST_ASSERT_EQUAL_INT(18, fixed_to_int(result));
}

/* Test 4D vector length */
void test_vector4_length(void) {
    vector4_t v = vector4_init_int(1, 2, 3, 5);
    fixed_t result = vector4_length(v);

    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(result));
}

/* Test 4D vector normalization */
void test_vector4_normalize(void) {
    vector4_t v = vector4_init_int(1, 3, 4, 12);
    vector4_t result = vector4_normalize(v);
    fixed_t length = vector4_length(result);

    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(length), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f / 13.0f, fixed_to_float(result.x), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(3.0f / 13.0f, fixed_to_float(result.y), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(4.0f / 13.0f, fixed_to_float(result.z), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(12.0f / 13.0f, fixed_to_float(result.w), 0.01f);
}

/* Special case - Test normalization with zero vector */
void test_vector_normalize_zero(void) {
    vector2_t v2 = vector2_init(FIXED_ZERO, FIXED_ZERO);
    vector3_t v3 = vector3_init(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);
    vector2_t result2 = vector2_normalize(v2);
    vector3_t result3 = vector3_normalize(v3);

    /* Should return zero vectors */
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result2.x));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result2.y));

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result3.x));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result3.y));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result3.z));
}

int main(void) {
    test_results_t results;

    /* Initialize the test framework */
    test_init(&results);

    /* Run Vector2 tests */
    test_begin_suite(&results, "Vector2 Operations");
    test_run(&results, test_vector2_init, "Vector2 Initialization");
    test_run(&results, test_vector2_init_int, "Vector2 Integer Initialization");
    test_run(&results, test_vector2_add, "Vector2 Addition");
    test_run(&results, test_vector2_sub, "Vector2 Subtraction");
    test_run(&results, test_vector2_scale, "Vector2 Scalar Multiplication");
    test_run(&results, test_vector2_dot, "Vector2 Dot Product");
    test_run(&results, test_vector2_length_squared, "Vector2 Length Squared");
    test_run(&results, test_vector2_length, "Vector2 Length");
    test_run(&results, test_vector2_normalize, "Vector2 Normalization");
    test_end_suite(&results);

    /* Run Vector3 tests */
    test_begin_suite(&results, "Vector3 Operations");
    test_run(&results, test_vector3_init, "Vector3 Initialization");
    test_run(&results, test_vector3_init_int, "Vector3 Integer Initialization");
    test_run(&results, test_vector3_add, "Vector3 Addition");
    test_run(&results, test_vector3_sub, "Vector3 Subtraction");
    test_run(&results, test_vector3_scale, "Vector3 Scalar Multiplication");
    test_run(&results, test_vector3_dot, "Vector3 Dot Product");
    test_run(&results, test_vector3_cross, "Vector3 Cross Product");
    test_run(&results, test_vector3_cross_anticommutative, "Vector3 Cross Anti-Commutative");
    test_run(&results, test_vector3_cross_basis, "Vector3 Cross Basis");
    test_run(&results, test_vector3_length_squared, "Vector3 Length Squared");
    test_run(&results, test_vector3_length, "Vector3 Length");
    test_run(&results, test_vector3_normalize, "Vector3 Normalization");
    test_end_suite(&results);

    /* Run Vector4 tests */
    test_begin_suite(&results, "Vector4 Operations");
    test_run(&results, test_vector4_init, "Vector4 Initialization");
    test_run(&results, test_vector4_init_int, "Vector4 Integer Initialization");
    test_run(&results, test_vector4_from_vec3, "Vector4 from Vector3");
    test_run(&results, test_vector4_add, "Vector4 Addition");
    test_run(&results, test_vector4_sub, "Vector4 Subtraction");
    test_run(&results, test_vector4_scale, "Vector4 Scalar Multiplication");
    test_run(&results, test_vector4_dot, "Vector4 Dot Product");
    test_run(&results, test_vector4_length_squared, "Vector4 Length Squared");
    test_run(&results, test_vector4_length, "Vector4 Length");
    test_run(&results, test_vector4_normalize, "Vector4 Normalization");
    test_end_suite(&results);

    /* Run special case tests */
    test_begin_suite(&results, "Special Case Tests");
    test_run(&results, test_vector_normalize_zero, "Normalization of Zero Vectors");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
