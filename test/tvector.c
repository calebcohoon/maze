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
    test_end_suite(&results);

    /* Run Vector3 tests */
    test_begin_suite(&results, "Vector3 Operations");
    test_run(&results, test_vector3_init, "Vector3 Initialization");
    test_run(&results, test_vector3_init_int, "Vector3 Integer Initialization");
    test_run(&results, test_vector3_add, "Vector3 Addition");
    test_run(&results, test_vector3_sub, "Vector3 Subtraction");
    test_run(&results, test_vector3_scale, "Vector3 Scalar Multiplication");
    test_end_suite(&results);

    /* Run Vector4 tests */
    test_begin_suite(&results, "Vector4 Operations");
    test_run(&results, test_vector4_init, "Vector4 Initialization");
    test_run(&results, test_vector4_init_int, "Vector4 Integer Initialization");
    test_run(&results, test_vector4_from_vec3, "Vector4 from Vector3");
    test_run(&results, test_vector4_add, "Vector4 Addition");
    test_run(&results, test_vector4_sub, "Vector4 Subtraction");
    test_run(&results, test_vector4_scale, "Vector4 Scalar Multiplication");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
