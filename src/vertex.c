/*
 * vertex.c
 *
 * Implementation of vertex system for 3D rendering pipeline
 */

#include "..\include\vertex.h"

#include <string.h>

/*
 * vertex_init: Initialize a vertex with position only
 *
 * Parameters:
 *   x, y, z - Position coordinates in fixed-point format
 *
 * Returns:
 *   Initialized vertex with default values for other properties
 */
vertex_t vertex_init(fixed_t x, fixed_t y, fixed_t z) {
    vertex_t result;

    /* Set position */
    result.position = vector3_init(x, y, z);

    /* Initialize normal */
    result.normal = vector3_init(FIXED_ZERO, FIXED_ZERO, FIXED_ONE);

    /* Initialize color to white */
    result.color.r = 255;
    result.color.g = 255;
    result.color.b = 255;

    /* Initialize texture coordinates to (0,0) */
    result.texcoord.u = FIXED_ZERO;
    result.texcoord.v = FIXED_ZERO;

    return result;
}

/*
 * vertex_init_vec: Initialize a vertex with position vector
 *
 * Parameters:
 *   position - Vector3 containing the position
 *
 * Returns:
 *   Initialized vertex with default values for other properties
 */
vertex_t vertex_init_vec(vector3_t position) {
    return vertex_init(position.x, position.y, position.z);
}

/*
 * vertex_set_normal_xyz: Set the normal vector of a vertex
 *
 * Parameters:
 *   v - Pointer to vertex to modify
 *   x, y, z - Normal vector components in fixed-point format
 */
void vertex_set_normal_xyz(vertex_t *v, fixed_t x, fixed_t y, fixed_t z) {
    if (v == NULL) {
        return;
    }

    v->normal = vector3_init(x, y, z);
}

/*
 * vertex_set_normal: Set the normal vector of a vertex
 *
 * Parameters:
 *   v - Pointer to vertex to modify
 *   normal - Vector3 containing the new normal
 */
void vertex_set_normal(vertex_t *v, vector3_t normal) {
    vertex_set_normal_xyz(v, normal.x, normal.y, normal.z);
}

/*
 * vertex_set_color_rgb: Set the color of a vertex using RGB components
 *
 * Parameters:
 *   v - Pointer to vertex to modify
 *   r, g, b - Color components (0-255)
 */
void vertex_set_color_rgb(vertex_t *v, unsigned char r, unsigned char g, unsigned char b) {
    if (v == NULL) {
        return;
    }

    v->color.r = r;
    v->color.g = g;
    v->color.b = b;
}

/*
 * vertex_set_color: Set the color of a vertex
 *
 * Parameters:
 *   v - Pointer to vertex to modify
 *   color - Color to assign to the vertex
 */
void vertex_set_color(vertex_t *v, color_t color) {
    vertex_set_color_rgb(v, color.r, color.g, color.b);
}

/*
 * vertex_set_texcoord_uv: Set the texture coordinates of a vertex using components
 *
 * Parameters:
 *   v - Pointer to vertex to modify
 *   u, v - Texture coordinate components in fixed-point format
 */
void vertex_set_texcoord_uv(vertex_t *v, fixed_t u, fixed_t v_coord) {
    if (v == NULL) {
        return;
    }

    v->texcoord.u = u;
    v->texcoord.v = v_coord;
}

/*
 * vertex_set_texcoord: Set the texture coordinates of a vertex
 *
 * Parameters:
 *   v - Pointer to vertex to modify
 *   texcoord - Texture coordinates to assign
 */
void vertex_set_texcoord(vertex_t *v, texcoord_t texcoord) {
    vertex_set_texcoord_uv(v, texcoord.u, texcoord.v);
}

/*
 * vertex_transform: Transform a vertex by a 4x4 matrix
 *
 * Parameters:
 *   v - Pointer to vertex transform
 *   m - Transformation matrix
 *
 * Returns:
 *   Transformed vertex (position only, normal is not transformed)
 */
vertex_t vertex_transform(const vertex_t *v, const matrix_t *m) {
    vertex_t result = *v;

    /* Tranform position */
    result.position = matrix_mul_vector3(m, &v->position);

    return result;
}

/*
 * vertex_transform_normal: Transform a vertex normal by a 4x4 matrix
 *
 * Parameters:
 *   v - Pointer to vertex transform
 *   m - Transformation matrix
 */
void vertex_transform_normal(vertex_t *v, const matrix_t *m) {
    matrix_t transpose;
    int i, j;

    /* Create transpose of the 3x3 upper-left portion of the matrix */
    transpose = matrix_init();

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            transpose.m[i][j] = m->m[j][i];
        }
    }

    transpose.m[3][3] = FIXED_ONE;

    /* Transform the normal using the transpose */
    v->normal = matrix_mul_vector3(&transpose, &v->normal);

    /* Re-normalize to prevent scaling effects */
    v->normal = vector3_normalize(v->normal);
}
