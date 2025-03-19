/*
 * triangle.c
 *
 * Implementation of triangle system for 3D rendering
 */

#include "..\include\triangle.h"

#include <string.h>

#include "..\include\defs.h"

/*
 * triangle_init: Initialize a triangle with three vertices
 *
 * Parameters:
 *   v1, v2, v3 - Three vertices forming the triangle
 *
 * Returns:
 *   Intialized triangle with calculated normal
 */
triangle_t triangle_init(vertex_t v1, vertex_t v2, vertex_t v3) {
    triangle_t result;

    /* Set vertices */
    result.vertices[0] = v1;
    result.vertices[1] = v2;
    result.vertices[2] = v3;

    /* Set default values */
    result.face_culled = FALSE;
    result.render_mode = TRIANGLE_FLAT;
    result.texture = NULL;

    /* Set default color to white */
    result.color.r = 255;
    result.color.g = 255;
    result.color.b = 255;

    /* Calculate surface normal */
    triangle_calculate_normal(&result);

    return result;
}

/*
 * triangle_calculate_normal: Calculate the surface normal of a triangle
 *
 * Parameters:
 *   t - Pointer to triangle to calculate normal for
 *
 * Notes:
 *   - Uses the cross product of two edges of the triangle
 *   - The normal is normalized to unit length for proper backface culling
 */
void triangle_calculate_normal(triangle_t *t) {
    vector3_t edge1, edge2;

    if (t == NULL) {
        return;
    }

    /* Calculate two edges of the triangle */
    edge1 = vector3_sub(t->vertices[1].position, t->vertices[0].position);
    edge2 = vector3_sub(t->vertices[2].position, t->vertices[0].position);

    /* Calculate normal using cross product */
    t->normal = vector3_cross(edge1, edge2);

    /* Normalize the normal */
    t->normal = vector3_normalize(t->normal);
}

/*
 * triangle_is_facing_camera: Determine if triangle faces the camera
 *
 * Parameters:
 *   t - Pointer to triangle to check
 *
 * Returns:
 *   TRUE if triangle is facing the camera, FALSE otherwise
 *
 * Notes:
 *   - Uses the cross product of two edges of the triangle
 *   - The normal is normalized to unit length for proper backface culling
 */
int triangle_is_facing_camera(const triangle_t *t) {
    if (t == NULL) {
        return FALSE;
    }

    /*
    In camera/view space, the camera looks down the negative Z axis
    so triangles facing the camera have positive Z normal components
    */
    return (t->normal.z < 0);
}

/*
 * triangle_transform: Transform a triangle by a 4x4 matrix
 *
 * Parameters:
 *   t - Pointer to triangle to transform
 *   m - Transformation matrix
 *
 * Returns:
 *   Transformed triangle with updated normal
 */
triangle_t triangle_transform(const triangle_t *t, const matrix_t *m) {
    triangle_t result;
    int i;

    if (t == NULL || m == NULL) {
        triangle_t empty;

        /* Initialize and return an empty triangle if inputs are invalid */
        empty.vertices[0] = vertex_init(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);
        empty.vertices[1] = vertex_init(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);
        empty.vertices[2] = vertex_init(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);
        empty.normal = vector3_init(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);
        empty.face_culled = TRUE;
        empty.color = t ? t->color : empty.color;
        empty.texture = NULL;
        empty.render_mode = TRIANGLE_FLAT;

        return empty;
    }

    /* Copy properties */
    result.color = t->color;
    result.face_culled = t->face_culled;
    result.texture = t->texture;
    result.render_mode = t->render_mode;

    /* Transform each vertex */
    for (i = 0; i < 3; i++) {
        result.vertices[i] = vertex_transform(&t->vertices[i], m);
    }

    /* Recalculate normal after transformation */
    triangle_calculate_normal(&result);

    return result;
}

/*
 * triangle_set_color: Set the flat shading color for a triangle
 *
 * Parameters:
 *   t - Pointer to triangle to modify
 *   color - Color to assign to the triangle
 */
void triangle_set_color(triangle_t *t, color_t color) {
    if (t == NULL) {
        return;
    }

    t->color = color;
}

/*
 * triangle_set_texture: Assign a texture to a triangle
 *
 * Parameters:
 *   t - Pointer to triangle to modify
 *   texture - Pointer to texture to assign
 */
void triangle_set_texture(triangle_t *t, texture_t *texture) {
    if (t == NULL) {
        return;
    }

    t->texture = texture;

    /* When setting a texture, automatically switch to textured mode */
    if (texture != NULL) {
        t->render_mode = TRIANGLE_TEXTURED;
    }
}

/*
 * triangle_set_render_mode: Set the rendering mode for a triangle
 *
 * Parameters:
 *   t - Pointer to triangle to modify
 *   mode - Render mode (TRIANGLE_FLAT or TRIANGLE_TEXTURED)
 *
 * Notes:
 *   - Setting TRIANGLE_TEXTURED mode requires a texture to be assigned
 */
void triangle_set_render_mode(triangle_t *t, int mode) {
    if (t == NULL) {
        return;
    }

    /* Only allow textured mode if a texture is assigned */
    if (mode == TRIANGLE_TEXTURED && t->texture == NULL) {
        return;
    }

    t->render_mode = mode;
}
