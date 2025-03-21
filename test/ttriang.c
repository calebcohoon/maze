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

/* Test normal calculation */
void test_triangle_calculate_normal(void) {
    /* Create a triangle on the XY plane */
    vertex_t v1 = vertex_init(fixed_from_int(0), fixed_from_int(0), fixed_from_int(0));
    vertex_t v2 = vertex_init(fixed_from_int(1), fixed_from_int(0), fixed_from_int(0));
    vertex_t v3 = vertex_init(fixed_from_int(0), fixed_from_int(1), fixed_from_int(0));
    triangle_t t = triangle_init(v1, v2, v3);

    /* Check normal - should be pointing along positive Z */
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(t.normal.x), 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(t.normal.y), 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(t.normal.z), 0.001f);

    /* Create a triangle in the YZ plane */
    v1 = vertex_init(fixed_from_int(0), fixed_from_int(0), fixed_from_int(0));
    v2 = vertex_init(fixed_from_int(0), fixed_from_int(1), fixed_from_int(0));
    v3 = vertex_init(fixed_from_int(0), fixed_from_int(0), fixed_from_int(1));
    t = triangle_init(v1, v2, v3);

    /* Check normal - should be pointing along positive X */
    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(t.normal.x), 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(t.normal.y), 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(t.normal.z), 0.001f);
}

/* Test camera facing check */
void test_triangle_is_facing_camera(void) {
    /* Create a triangle facing towards positive Z */
    vertex_t v1 = vertex_init(fixed_from_int(0), fixed_from_int(0), fixed_from_int(0));
    vertex_t v2 = vertex_init(fixed_from_int(1), fixed_from_int(0), fixed_from_int(0));
    vertex_t v3 = vertex_init(fixed_from_int(0), fixed_from_int(1), fixed_from_int(0));
    triangle_t t = triangle_init(v1, v2, v3);

    /* Camera looks down negative Z axis, triangle normal points positive Z
       so it should not be facing the camera */
    TEST_ASSERT_EQUAL_INT(FALSE, triangle_is_facing_camera(&t));

    /* Create a triangle facing towards negative Z */
    v1 = vertex_init(fixed_from_int(0), fixed_from_int(0), fixed_from_int(0));
    v2 = vertex_init(fixed_from_int(0), fixed_from_int(1), fixed_from_int(0));
    v3 = vertex_init(fixed_from_int(1), fixed_from_int(0), fixed_from_int(0));
    t = triangle_init(v1, v2, v3);

    /* Camera looks down negative Z axis, triangle normal points negative Z
       so it should be facing the camera */
    TEST_ASSERT_EQUAL_INT(TRUE, triangle_is_facing_camera(&t));
}

/* Test triangle transformation */
void test_triangle_transform(void) {
    /* Create a triangle on the XY plane */
    vertex_t v1 = vertex_init(fixed_from_int(0), fixed_from_int(0), fixed_from_int(0));
    vertex_t v2 = vertex_init(fixed_from_int(1), fixed_from_int(0), fixed_from_int(0));
    vertex_t v3 = vertex_init(fixed_from_int(0), fixed_from_int(1), fixed_from_int(0));
    triangle_t t = triangle_init(v1, v2, v3);
    triangle_t result;
    matrix_t trans;

    /* Create a translation matrix */
    trans = matrix_translation(fixed_from_int(5), fixed_from_int(10), fixed_from_int(15));

    /* Transform the triangle */
    result = triangle_transform(&t, &trans);

    /* Check transformed positions */
    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result.vertices[0].position.x));
    TEST_ASSERT_EQUAL_INT(10, fixed_to_int(result.vertices[0].position.y));
    TEST_ASSERT_EQUAL_INT(15, fixed_to_int(result.vertices[0].position.z));

    TEST_ASSERT_EQUAL_INT(6, fixed_to_int(result.vertices[1].position.x));
    TEST_ASSERT_EQUAL_INT(10, fixed_to_int(result.vertices[1].position.y));
    TEST_ASSERT_EQUAL_INT(15, fixed_to_int(result.vertices[1].position.z));

    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result.vertices[2].position.x));
    TEST_ASSERT_EQUAL_INT(11, fixed_to_int(result.vertices[2].position.y));
    TEST_ASSERT_EQUAL_INT(15, fixed_to_int(result.vertices[2].position.z));

    /* Normal should still point in the Z direction after translation */
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(result.normal.x), 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(result.normal.y), 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, fixed_to_float(result.normal.z), 0.001f);
}

/* Test normal transformation with rotation */
void test_triangle_transform_normal(void) {
    /* Create a triangle on the XY plane */
    vertex_t v1 = vertex_init(fixed_from_int(0), fixed_from_int(0), fixed_from_int(0));
    vertex_t v2 = vertex_init(fixed_from_int(1), fixed_from_int(0), fixed_from_int(0));
    vertex_t v3 = vertex_init(fixed_from_int(0), fixed_from_int(1), fixed_from_int(0));
    triangle_t t = triangle_init(v1, v2, v3);
    triangle_t result;
    matrix_t rot;

    /* Initialize trig tables for rotation */
    trig_init();

    /* Create rotation matrix to rotate 90 degrees around X axis */
    rot = matrix_rotation_x(64);

    /* Transform the triangle */
    result = triangle_transform(&t, &rot);

    /* Normal should now point along negative Y axis after rotation */
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(result.normal.x), 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, fixed_to_float(result.normal.y), 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, fixed_to_float(result.normal.z), 0.001f);
}

/* Test color setting */
void test_triangle_set_color(void) {
    /* Create a triangle on the XY plane */
    vertex_t v1 = vertex_init(fixed_from_int(0), fixed_from_int(0), fixed_from_int(0));
    vertex_t v2 = vertex_init(fixed_from_int(1), fixed_from_int(0), fixed_from_int(0));
    vertex_t v3 = vertex_init(fixed_from_int(0), fixed_from_int(1), fixed_from_int(0));
    triangle_t t = triangle_init(v1, v2, v3);
    color_t color = {128, 64, 32};

    /* Set the color */
    triangle_set_color(&t, color);

    /* Check color components */
    TEST_ASSERT_EQUAL_INT(128, t.color.r);
    TEST_ASSERT_EQUAL_INT(64, t.color.g);
    TEST_ASSERT_EQUAL_INT(32, t.color.b);
}

/* Test texture setting */
void test_triangle_set_texture(void) {
    /* Create a triangle on the XY plane */
    vertex_t v1 = vertex_init(fixed_from_int(0), fixed_from_int(0), fixed_from_int(0));
    vertex_t v2 = vertex_init(fixed_from_int(1), fixed_from_int(0), fixed_from_int(0));
    vertex_t v3 = vertex_init(fixed_from_int(0), fixed_from_int(1), fixed_from_int(0));
    triangle_t t = triangle_init(v1, v2, v3);
    texture_t texture;
    unsigned char texture_data[64 * 64];

    /* Initialize test texture */
    texture.texture_data = texture_data;
    texture.width = 64;
    texture.height = 64;

    /* Set the texture */
    triangle_set_texture(&t, &texture);

    /* Check texture association */
    TEST_ASSERT("Texture is set", t.texture == &texture);
    TEST_ASSERT_EQUAL_INT(TRIANGLE_TEXTURED, t.render_mode);
}

/* Test render mode setting */
void test_triangle_set_render_mode(void) {
    /* Create a triangle on the XY plane */
    vertex_t v1 = vertex_init(fixed_from_int(0), fixed_from_int(0), fixed_from_int(0));
    vertex_t v2 = vertex_init(fixed_from_int(1), fixed_from_int(0), fixed_from_int(0));
    vertex_t v3 = vertex_init(fixed_from_int(0), fixed_from_int(1), fixed_from_int(0));
    triangle_t t = triangle_init(v1, v2, v3);
    texture_t texture;
    unsigned char texture_data[64 * 64];

    /* Initialize test texture */
    texture.texture_data = texture_data;
    texture.width = 64;
    texture.height = 64;

    /* Try to set textured mode without texture */
    triangle_set_render_mode(&t, TRIANGLE_TEXTURED);

    /* Should still be flat as no texture assigned */
    TEST_ASSERT_EQUAL_INT(TRIANGLE_FLAT, t.render_mode);

    /* Set texture and try again */
    triangle_set_texture(&t, &texture);
    triangle_set_render_mode(&t, TRIANGLE_TEXTURED);

    /* Not should be textured */
    TEST_ASSERT_EQUAL_INT(TRIANGLE_TEXTURED, t.render_mode);

    /* Set back to flat */
    triangle_set_render_mode(&t, TRIANGLE_FLAT);
    TEST_ASSERT_EQUAL_INT(TRIANGLE_FLAT, t.render_mode);
}

/* Test null handling */
void test_triangle_null_handling(void) {
    triangle_t result;
    color_t color = {0, 0, 0};

    /* Null pointer tests should not crash */
    triangle_calculate_normal(NULL);

    TEST_ASSERT_EQUAL_INT(FALSE, triangle_is_facing_camera(NULL));

    triangle_set_color(NULL, color);

    triangle_set_texture(NULL, NULL);

    triangle_set_render_mode(NULL, 0);

    /* Test transform with null pointers */
    result = triangle_transform(NULL, NULL);

    TEST_ASSERT_EQUAL_INT(TRUE, result.face_culled);
}

int main(void) {
    test_results_t results;

    /* Initialize the test framework */
    test_init(&results);

    /* Run basic triangle creation tests */
    test_begin_suite(&results, "Triangle Initialization");
    test_run(&results, test_triangle_init, "Basic Initialization");
    test_end_suite(&results);

    /* Run normal calculation tests */
    test_begin_suite(&results, "Triangle Normal Calculation");
    test_run(&results, test_triangle_calculate_normal, "Normal Calculation");
    test_run(&results, test_triangle_is_facing_camera, "Camera Facing Check");
    test_end_suite(&results);

    /* Run transformation tests */
    test_begin_suite(&results, "Triangle Transformation");
    test_run(&results, test_triangle_transform, "Position Transformation");
    test_run(&results, test_triangle_transform_normal, "Normal Transformation");
    test_end_suite(&results);

    /* Run property tests */
    test_begin_suite(&results, "Triangle Properties");
    test_run(&results, test_triangle_set_color, "Color Setting");
    test_run(&results, test_triangle_set_texture, "Texture Setting");
    test_run(&results, test_triangle_set_render_mode, "Render Mode Setting");
    test_end_suite(&results);

    /* Run robustness tests */
    test_begin_suite(&results, "Triangle Robustness");
    test_run(&results, test_triangle_null_handling, "Null Pointer Handling");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
