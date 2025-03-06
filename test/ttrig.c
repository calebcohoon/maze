/*
 * ttrig.c
 *
 * Test suite for trigonometry functions
 */

#include <math.h>
#include <stdio.h>

#include "..\include\trig.h"
#include "tmath.h"

/* Test table initialization and basic lookup */
void test_trig_init(void) {
    const fixed_t *sine_table;

    /* Initialize the table */
    trig_init();

    /* Get table pointer for inspection */
    sine_table = trig_get_table();

    /* Verify first entry sin(0) = 0 */
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(sine_table[0]), 0.01f);

    /* Verify sin(90) = 1 */
    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(sine_table[64]), 0.01f);

    /* Verify sin(180) = 0 */
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(sine_table[128]), 0.01f);

    /* Verify sin(270) = -1.0 */
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, fixed_to_float(sine_table[192]), 0.01f);
}

int main(void) {
    test_results_t results;

    /* Initialize the test framework */
    test_init(&results);

    /* Run trigonometry table initialization tests */
    test_begin_suite(&results, "Trigonometry Table Initialization");
    test_run(&results, test_trig_init, "Table Initialization");
    test_end_suite(&results);

    return 0;
}