/*
 * tvertex.c
 *
 * Test suite for vertex operations
 */

#include <stdio.h>

#include "..\include\matrix.h"
#include "..\include\trig.h"
#include "..\include\vertex.h"
#include "tmath.h"

/* Test vertex initialization */
void test_vertex_init(void) {
    vertex_t v = vertex_init(fixed_from_int(1), fixed_from_int(2), fixed_from_int(3));

    /* Check position components */
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(v.position.x));
    TEST_ASSERT_EQUAL_INT(2, fixed_to_int(v.position.y));
    TEST_ASSERT_EQUAL_INT(3, fixed_to_int(v.position.z));

    /* Check default normal */
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(v.normal.x));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(v.normal.y));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(v.normal.z));

    /* Check default color */
    TEST_ASSERT_EQUAL_INT(255, v.color.r);
    TEST_ASSERT_EQUAL_INT(255, v.color.g);
    TEST_ASSERT_EQUAL_INT(255, v.color.b);

    /* Check default UV */
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(v.texcoord.u));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(v.texcoord.v));
}

/* Test vertex initialization with vector */
void test_vertex_init_vec(void) {
    vector3_t pos = vector3_init_int(4, 5, 6);
    vertex_t v = vertex_init_vec(pos);

    /* Check position components */
    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(v.position.x));
    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(v.position.y));
    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(v.position.z));
}

/* Test setting vertex normal */
void test_vertex_set_normal(void) {
    vector3_t normal = vector3_init_int(1, 0, 0);
    vertex_t v = vertex_init(fixed_from_int(1), fixed_from_int(1), fixed_from_int(1));

    vertex_set_normal(&v, normal);

    /* Check normal components */
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(v.normal.x));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(v.normal.y));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(v.normal.z));
}

/* Test setting vertex normal by components */
void test_vertex_set_normal_xyz(void) {
    vertex_t v = vertex_init(fixed_from_int(1), fixed_from_int(1), fixed_from_int(1));

    vertex_set_normal_xyz(&v, fixed_from_int(0), fixed_from_int(1), fixed_from_int(0));

    /* Check normal components */
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(v.normal.x));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(v.normal.y));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(v.normal.z));
}

/* Test setting vertex color */
void test_vertex_set_color(void) {
    vertex_t v = vertex_init(fixed_from_int(1), fixed_from_int(1), fixed_from_int(1));
    color_t color = {128, 64, 32};

    vertex_set_color(&v, color);

    /* Check color components */
    TEST_ASSERT_EQUAL_INT(128, v.color.r);
    TEST_ASSERT_EQUAL_INT(64, v.color.g);
    TEST_ASSERT_EQUAL_INT(32, v.color.b);
}

/* Test setting vertex color by components */
void test_vertex_set_color_rgb(void) {
    vertex_t v = vertex_init(fixed_from_int(1), fixed_from_int(1), fixed_from_int(1));

    vertex_set_color_rgb(&v, 32, 64, 128);

    /* Check color components */
    TEST_ASSERT_EQUAL_INT(32, v.color.r);
    TEST_ASSERT_EQUAL_INT(64, v.color.g);
    TEST_ASSERT_EQUAL_INT(128, v.color.b);
}

/* Test setting texture coordinates */
void test_vertex_set_texcoord(void) {
    vertex_t v = vertex_init(fixed_from_int(1), fixed_from_int(1), fixed_from_int(1));
    texcoord_t texcoord;

    texcoord.u = fixed_from_float(0.25f);
    texcoord.v = fixed_from_float(0.75f);

    vertex_set_texcoord(&v, texcoord);

    /* Check texcoord components */
    TEST_ASSERT_EQUAL_FLOAT(0.25f, fixed_to_float(v.texcoord.u), 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(0.75f, fixed_to_float(v.texcoord.v), 0.001f);
}

/* Test setting texture coordinates by components */
void test_vertex_set_texcoord_uv(void) {
    vertex_t v = vertex_init(fixed_from_int(1), fixed_from_int(1), fixed_from_int(1));

    vertex_set_texcoord_uv(&v, fixed_from_float(0.125f), fixed_from_float(0.875f));

    /* Check texcoord components */
    TEST_ASSERT_EQUAL_FLOAT(0.125f, fixed_to_float(v.texcoord.u), 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(0.875f, fixed_to_float(v.texcoord.v), 0.001f);
}

/* Test vertex transformation */
void test_vertex_transform(void) {
    vertex_t v = vertex_init(fixed_from_int(1), fixed_from_int(2), fixed_from_int(3));
    matrix_t m = matrix_identity();
    vertex_t result;

    /* Set up translation matrix */
    m.m[0][3] = fixed_from_int(10);  // X translation
    m.m[1][3] = fixed_from_int(20);  // Y translation
    m.m[2][3] = fixed_from_int(30);  // Z translation

    result = vertex_transform(&v, &m);

    /* Check position after transformation */
    TEST_ASSERT_EQUAL_INT(11, fixed_to_int(result.position.x));
    TEST_ASSERT_EQUAL_INT(22, fixed_to_int(result.position.y));
    TEST_ASSERT_EQUAL_INT(33, fixed_to_int(result.position.z));

    /* Normal should remain unchanged */
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.normal.x));
    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result.normal.y));
    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result.normal.z));
}

/* Test normal transformation */
void test_vertex_transform_normal(void) {
    vertex_t v = vertex_init(fixed_from_int(1), fixed_from_int(2), fixed_from_int(3));
    matrix_t m = matrix_identity();

    /* Initialize trig tables for rotation */
    trig_init();

    /* Set normal to (0,0,1) */
    vertex_set_normal_xyz(&v, FIXED_ZERO, FIXED_ZERO, FIXED_ONE);

    /* Create rotation matrix to rotate 90 degrees around X axis */
    m = matrix_rotation_x(64);  // 90 deg

    /* Transform the normal */
    vertex_transform_normal(&v, &m);

    /* Check the transformed normal */
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(v.normal.x), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(v.normal.y), 0.01f);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(v.normal.z), 0.01f);
}

int main(void) {
    test_results_t results;

    /* Initialize the test framework */
    test_init(&results);

    /* Run basic vertex creation tests */
    test_begin_suite(&results, "Vertex Initialization");
    test_run(&results, test_vertex_init, "Basic Initialization");
    test_run(&results, test_vertex_init_vec, "Vector Initialization");
    test_end_suite(&results);

    /* Run vertex attribute setting tests */
    test_begin_suite(&results, "Vertex Attributes");
    test_run(&results, test_vertex_set_normal, "Set Normal Vector");
    test_run(&results, test_vertex_set_normal_xyz, "Set Normal Components");
    test_run(&results, test_vertex_set_color, "Set Color");
    test_run(&results, test_vertex_set_color_rgb, "Set Color Components");
    test_run(&results, test_vertex_set_texcoord, "Set Texture Coordinates");
    test_run(&results, test_vertex_set_texcoord_uv, "Set UV Components");
    test_end_suite(&results);

    /* Run vertex transformation tests */
    test_begin_suite(&results, "Vertex Transformation");
    test_run(&results, test_vertex_transform, "Position Transformation");
    test_run(&results, test_vertex_transform_normal, "Normal Transformation");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
