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
    sine_table = trig_get_sine_table();

    /* Verify first entry sin(0) = 0 */
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(sine_table[0]), 0.01f);

    /* Verify sin(90) = 1 */
    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(sine_table[64]), 0.01f);

    /* Verify sin(180) = 0 */
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(sine_table[128]), 0.01f);

    /* Verify sin(270) = -1.0 */
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, fixed_to_float(sine_table[192]), 0.01f);
}

/* Test sine lookup at cardinal points */
void test_trig_sine_cardinal(void) {
    /* Initialize the table */
    trig_init();

    /* Test cardinal angles */
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(trig_sine(0)), 0.01f);     // 0 deg
    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(trig_sine(64)), 0.01f);    // 90 deg
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(trig_sine(128)), 0.01f);   // 180 deg
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, fixed_to_float(trig_sine(192)), 0.01f);  // 270 deg
}

/* Test sine lookup at intermediate angles */
void test_trig_sine_intermediate(void) {
    /* Initialize the table */
    trig_init();

    /* Test intermediate angles */
    TEST_ASSERT_EQUAL_FLOAT(0.7071f, fixed_to_float(trig_sine(32)), 0.01f);    // 45 deg
    TEST_ASSERT_EQUAL_FLOAT(0.7071f, fixed_to_float(trig_sine(96)), 0.01f);    // 135 deg
    TEST_ASSERT_EQUAL_FLOAT(-0.7071f, fixed_to_float(trig_sine(160)), 0.01f);  // 225 deg
    TEST_ASSERT_EQUAL_FLOAT(-0.7071f, fixed_to_float(trig_sine(224)), 0.01f);  // 315 deg
}

/* Test cosine lookup at cardinal points */
void test_trig_cosine_cardinal(void) {
    /* Initialize the table */
    trig_init();

    /* Test cardinal angles */
    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(trig_cosine(0)), 0.01f);     // 0 deg
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(trig_cosine(64)), 0.01f);    // 90 deg
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, fixed_to_float(trig_cosine(128)), 0.01f);  // 180 deg
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(trig_cosine(192)), 0.01f);   // 270 deg
}

/* Test cosine lookup at intermediate angles */
void test_trig_cosine_intermediate(void) {
    /* Initialize the table */
    trig_init();

    /* Test intermediate angles */
    TEST_ASSERT_EQUAL_FLOAT(0.7071f, fixed_to_float(trig_cosine(32)), 0.01f);    // 45 deg
    TEST_ASSERT_EQUAL_FLOAT(-0.7071f, fixed_to_float(trig_cosine(96)), 0.01f);   // 135 deg
    TEST_ASSERT_EQUAL_FLOAT(-0.7071f, fixed_to_float(trig_cosine(160)), 0.01f);  // 225 deg
    TEST_ASSERT_EQUAL_FLOAT(0.7071f, fixed_to_float(trig_cosine(224)), 0.01f);   // 315 deg
}

/* Test sine-cosine relationships */
void test_trig_sin_cos_relation(void) {
    unsigned char angle;
    fixed_t sin_squared, cos_squared, sum;

    /* Initialize the table */
    trig_init();

    /* Test sin^2(theta) + cos^2(theta) = 1 for various angles */
    for (angle = 0; angle < 64; angle += 16) {
        sin_squared = fixed_mul(trig_sine(angle), trig_sine(angle));
        cos_squared = fixed_mul(trig_cosine(angle), trig_cosine(angle));
        sum = fixed_add(sin_squared, cos_squared);

        TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(sum), 0.01f);
    }

    /* Also test specific angles */
    angle = 33;  // Random angle
    sin_squared = fixed_mul(trig_sine(angle), trig_sine(angle));
    cos_squared = fixed_mul(trig_cosine(angle), trig_cosine(angle));
    sum = fixed_add(sin_squared, cos_squared);

    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(sum), 0.01f);
}

/* Test angle wrapping behavior */
void test_trig_angle_wrapping(void) {
    unsigned char angle1, angle2;

    /* Initialize the table */
    trig_init();

    /* Test that angles wrap correctly - angle = angle % 256 */
    /* These should be equal: 270 deg and 270 deg + 360 deg */
    angle1 = 192;
    angle2 = angle1 + 256;
    TEST_ASSERT_EQUAL_FLOAT(
        fixed_to_float(trig_sine(angle1)), fixed_to_float(trig_sine(angle2)), 0.001f);

    /* These should be equal: 90 deg and 90 deg + 360 deg */
    angle1 = 64;
    angle2 = angle1 + 256;
    TEST_ASSERT_EQUAL_FLOAT(
        fixed_to_float(trig_sine(angle1)), fixed_to_float(trig_sine(angle2)), 0.001f);
}

/* Test tangent lookup at cardinal points */
void test_trig_tangent_cardinal(void) {
    /* Initialize the table */
    trig_init();

    /* Test cardinal angles */
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(trig_tangent(0)), 0.01f);
    TEST_ASSERT("Tangent at 90 deg should be invalid", trig_tangent(64) == TRIG_TAN_INVALID);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(trig_tangent(128)), 0.01f);
    TEST_ASSERT("Tangent at 270 deg should be invalid", trig_tangent(192) == TRIG_TAN_INVALID);
}

/* Test tangent lookup at intermediate angles */
void test_trig_tangent_intermediate(void) {
    /* Initialize the table */
    trig_init();

    /* Test intermediate angles */
    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(trig_tangent(32)), 0.01f);    // 45 deg
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, fixed_to_float(trig_tangent(96)), 0.01f);   // 135 deg
    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(trig_tangent(160)), 0.01f);   // 225 deg
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, fixed_to_float(trig_tangent(224)), 0.01f);  // 315 deg
}

/* Test tangent values near singularities */
void test_trig_tangent_near_singularities(void) {
    /* Initialize the table */
    trig_init();

    /* Test near 90 deg */
    TEST_ASSERT("Tangent before 90 deg should be positive", trig_tangent(60) > 0);

    TEST_ASSERT("Tangent after 90 deg should be negative", trig_tangent(68) < 0);

    /* Test near 180 deg */
    TEST_ASSERT("Tangent before 180 deg should be negative", trig_tangent(126) < 0);

    TEST_ASSERT("Tangent after 180 deg should be positive", trig_tangent(130) > 0);
}

/* Test tangent relationships with sine and cosine */
void test_trig_tangent_relation(void) {
    unsigned char angle;
    fixed_t sine, cosine, tangent, calculated_tangent;

    /* Initialize the table */
    trig_init();

    /* Test that tan(theta) = sin(theta)/cos(theta) for various angles */
    /* Skip angles near 90 deg and 270 deg where division would be problematic */
    for (angle = 16; angle < 48; angle += 16) {
        sine = trig_sine(angle);
        cosine = trig_cosine(angle);
        tangent = trig_tangent(angle);
        calculated_tangent = fixed_div(sine, cosine);

        TEST_ASSERT_EQUAL_FLOAT(fixed_to_float(tangent), fixed_to_float(calculated_tangent), 0.01f);
    }
}

int main(void) {
    test_results_t results;

    /* Initialize the test framework */
    test_init(&results);

    /* Run trigonometry table initialization tests */
    test_begin_suite(&results, "Trigonometry Table Initialization");
    test_run(&results, test_trig_init, "Table Initialization");
    test_end_suite(&results);

    /* Run sine function tests */
    test_begin_suite(&results, "Sine Function Tests");
    test_run(&results, test_trig_sine_cardinal, "Sine at Cardinal Angles");
    test_run(&results, test_trig_sine_intermediate, "Sine at Intermediate Angles");
    test_end_suite(&results);

    /* Run cosine function tests */
    test_begin_suite(&results, "Cosine Function Tests");
    test_run(&results, test_trig_cosine_cardinal, "Cosine at Cardinal Angles");
    test_run(&results, test_trig_cosine_intermediate, "Cosine at Intermediate Angles");
    test_end_suite(&results);

    /* Run tangent function tests */
    test_begin_suite(&results, "Tangent Function Tests");
    test_run(&results, test_trig_tangent_cardinal, "Tangent at Cardinal Angles");
    test_run(&results, test_trig_tangent_intermediate, "Tangent at Intermediate Angles");
    test_run(&results, test_trig_tangent_near_singularities, "Tangent Near Singularities");
    test_run(&results, test_trig_tangent_relation, "Tangent Sine/Cosine Relationship");
    test_end_suite(&results);

    /* Run relationship tests */
    test_begin_suite(&results, "Trigonometric Relationships");
    test_run(&results, test_trig_sin_cos_relation, "Sine and Cosine Relation");
    test_run(&results, test_trig_angle_wrapping, "Angle Wrapping");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
