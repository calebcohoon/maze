/*
 * vertex.h
 *
 * Vertex system for 3D rendering pipeline
 * Defines structures and operations for manipulating 3D vertices
 */

#ifndef VERTEX_H
#define VERTEX_H

#include "fixed.h"
#include "matrix.h"
#include "vector.h"

/* Color definition using 8-bit components */
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} color_t;

/* UV texture coordinate */
typedef struct {
    fixed_t u;
    fixed_t v;
} texcoord_t;

/* Vertex structure */
typedef struct {
    vector3_t position;
    vector3_t normal;
    color_t color;
    texcoord_t texcoord;
} vertex_t;

/* Function prototypes */
vertex_t vertex_init(fixed_t x, fixed_t y, fixed_t z);
vertex_t vertex_init_vec(vector3_t position);
void vertex_set_normal_xyz(vertex_t *v, fixed_t x, fixed_t y, fixed_t z);
void vertex_set_normal(vertex_t *v, vector3_t normal);
void vertex_set_color_rgb(vertex_t *v, unsigned char r, unsigned char g, unsigned char b);
void vertex_set_color(vertex_t *v, color_t color);
void vertex_set_texcoord_uv(vertex_t *v, fixed_t u, fixed_t v_coord);
void vertex_set_texcoord(vertex_t *v, texcoord_t texcoord);
vertex_t vertex_transform(const vertex_t *v, const matrix_t *m);
void vertex_transform_normal(vertex_t *v, const matrix_t *m);

#endif /* VERTEX_H */
