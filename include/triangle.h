/*
 * triangle.h
 *
 * Triangle system for 3D rendering
 * Defines structures and operations for manipulating triangles
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "fixed.h"
#include "matrix.h"
#include "vertex.h"

/* Texture reference */
typedef struct {
    unsigned char *texture_data;  // Pointer to texture bitmap data
    int width;                    // Texture width in pixels
    int height;                   // Texture height in pixels
} texture_t;

/* Triangle render modes */
#define TRIANGLE_FLAT     0  // Flat shaded triangle
#define TRIANGLE_TEXTURED 1  // Textured triangle

/* Triangle structure */
typedef struct {
    vertex_t vertices[3];  // Array of three vertices forming the triangle
    vector3_t normal;      // Surface normal vector
    int face_culled;       // Flag indicating if this triangle is culled
    color_t color;         // Triangle color for flat shading
    texture_t *texture;    // Texture reference
    int render_mode;       // Rendering mode
} triangle_t;

/* Function prototypes */
triangle_t triangle_init(vertex_t v1, vertex_t v2, vertex_t v3);
void triangle_calculate_normal(triangle_t *t);
int triangle_is_facing_camera(const triangle_t *t);
triangle_t triangle_transform(const triangle_t *t, const matrix_t *m);
void triangle_set_color(triangle_t *t, color_t color);
void triangle_set_texture(triangle_t *t, texture_t *texture);
void triangle_set_render_mode(triangle_t *t, int mode);

#endif /* TRIANGLE_H */
