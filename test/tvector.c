/*
 * tvector.c
 *
 * Test suite for vector mathematics implementation
 */

#include <stdio.h>

#include "..\include\vector.h"
#include "tmath.h"

/* Vector2 tests */
int test_vector2_init(void) {
    vector2_t v = vector2_init(FIXED_ONE, FIXED_ONE * 2);

    TEST_ASSERT("Initialized vector2 has wrong values",
                1 == fixed_to_int(v.x) && 2 == fixed_to_int(v.y));
}

int test_vector2_init_int(void) {
    vector2_t v = vector2_init_int(3, 4);

    TEST_ASSERT("Initialized vector2 has wrong values",
                3 == fixed_to_int(v.x) && 4 == fixed_to_int(v.y));
}

/* Vector3 tests */
int test_vector3_init(void) {
    vector3_t v = vector3_init(FIXED_ONE, FIXED_ONE * 2, FIXED_ONE * 3);

    TEST_ASSERT("Initialized vector3 has wrong values",
                1 == fixed_to_int(v.x) && 2 == fixed_to_int(v.y) && 3 == fixed_to_int(v.z));
}

int test_vector3_init_int(void) {
    vector3_t v = vector3_init_int(4, 5, 6);

    TEST_ASSERT("Initialized vector3 has wrong values",
                4 == fixed_to_int(v.x) && 5 == fixed_to_int(v.y) && 6 == fixed_to_int(v.z));
}

/* Vector4 tests */
int test_vector4_init(void) {
    vector4_t v = vector4_init(FIXED_ONE, FIXED_ONE * 2, FIXED_ONE * 3, FIXED_ONE * 4);

    TEST_ASSERT("Initialized vector4 has wrong values",
                1 == fixed_to_int(v.x) && 2 == fixed_to_int(v.y) && 3 == fixed_to_int(v.z) &&
                    4 == fixed_to_int(v.w));
}

int test_vector4_init_int(void) {
    vector4_t v = vector4_init_int(5, 6, 7, 8);

    TEST_ASSERT("Initialized vector4 has wrong values",
                5 == fixed_to_int(v.x) && 6 == fixed_to_int(v.y) && 7 == fixed_to_int(v.z) &&
                    8 == fixed_to_int(v.w));
}

int test_vector4_from_vec3(void) {
    vector3_t v3 = vector3_init_int(1, 2, 3);
    vector4_t v4 = vector4_from_vec3(v3, FIXED_ONE);

    TEST_ASSERT("Vector4 from vector3 has wrong values",
                1 == fixed_to_int(v4.x) && 2 == fixed_to_int(v4.y) && 3 == fixed_to_int(v4.z) &&
                    1 == fixed_to_int(v4.w));
}

int main(void) {
    test_results_t results;

    /* Initialize the test framework */
    test_init(&results);

    /* Run Vector2 tests */
    test_begin_suite(&results, "Vector2 Operations");
    test_run(&results, test_vector2_init, "Vector2 Initialization");
    test_run(&results, test_vector2_init_int, "Vector2 Integer Initialization");
    test_end_suite(&results);

    /* Run Vector3 tests */
    test_begin_suite(&results, "Vector3 Operations");
    test_run(&results, test_vector3_init, "Vector3 Initialization");
    test_run(&results, test_vector3_init_int, "Vector3 Integer Initialization");
    test_end_suite(&results);

    /* Run Vector4 tests */
    test_begin_suite(&results, "Vector4 Operations");
    test_run(&results, test_vector4_init, "Vector4 Initialization");
    test_run(&results, test_vector4_init_int, "Vector4 Integer Initialization");
    test_run(&results, test_vector4_from_vec3, "Vector4 from Vector3");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
