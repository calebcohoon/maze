/*
 * ttriang.c
 *
 * Test suite for triangle system
 */

#include <stdio.h>

#include "..\include\matrix.h"
#include "..\include\triangle.h"
#include "..\include\trig.h"
#include "..\include\vertex.h"
#include "tmath.h"

/* Test triangle initialization */
void test_triangle_init(void) {
    vertex_t v1 = vertex_init(fixed_from_int(0), fixed_from_int(0), fixed_from_int(0));
    vertex_t v2 = vertex_init(fixed_from_int(1), fixed_from_int(0), fixed_from_int(0));
    vertex_t v3 = vertex_init(fixed_from_int(0), fixed_from_int(1), fixed_from_int(0));
    triangle_t t = triangle_init(v1, v2, v3);

    /* Check vertices */
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(t.vertices[0].position.x));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(t.vertices[0].position.y));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(t.vertices[0].position.z));

    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(t.vertices[1].position.x));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(t.vertices[1].position.y));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(t.vertices[1].position.z));

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(t.vertices[2].position.x));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(t.vertices[2].position.y));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(t.vertices[2].position.z));

    /* Check default values */
    TEST_ASSERT_EQUAL_INT(FALSE, t.face_culled);
    TEST_ASSERT_EQUAL_INT(TRIANGLE_FLAT, t.render_mode);
    TEST_ASSERT("Texture is NULL", t.texture == NULL);

    /* Check color */
    TEST_ASSERT_EQUAL_INT(255, t.color.r);
    TEST_ASSERT_EQUAL_INT(255, t.color.g);
    TEST_ASSERT_EQUAL_INT(255, t.color.b);
}

int main(void) {
    test_results_t results;

    /* Initialize the test framework */
    test_init(&results);

    /* Run basic triangle creation tests */
    test_begin_suite(&results, "Triangle Initialization");
    test_run(&results, test_triangle_init, "Basic Initialization");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
