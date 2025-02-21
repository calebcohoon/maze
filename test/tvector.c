/*
 * tvector.c
 *
 * Test suite for vector mathematics implementation
 */

#include <stdio.h>

#include "..\include\vector.h"
#include "tmath.h"

/* Vector2 test */
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

int main(void) {
    test_results_t results;

    /* Initialize the test framework */
    test_init(&results);

    /* Run Vector2 tests */
    test_begin_suite(&results, "Vector2 Operations");
    test_run(&results, test_vector2_init, "Vector2 Initialization");
    test_run(&results, test_vector2_init_int, "Vector2 Integer Initialization");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
