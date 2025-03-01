/*
 * vector.h
 *
 * Vector mathematics implementation using fixed-point arithmetic
 * Provides 2D, 3D, and 4D vector operations
 */

#ifndef VECTOR_H
#define VECTOR_H

#include "fixed.h"

/* Type definitions */
typedef struct {
    fixed_t x;
    fixed_t y;
} vector2_t;

typedef struct {
    fixed_t x;
    fixed_t y;
    fixed_t z;
} vector3_t;

typedef struct {
    fixed_t x;
    fixed_t y;
    fixed_t z;
    fixed_t w;
} vector4_t;

/* Vector2 function prototypes */
vector2_t vector2_init(fixed_t x, fixed_t y);
vector2_t vector2_init_int(int x, int y);
vector2_t vector2_add(vector2_t a, vector2_t b);
vector2_t vector2_sub(vector2_t a, vector2_t b);
vector2_t vector2_scale(vector2_t v, fixed_t s);
fixed_t vector2_dot(vector2_t a, vector2_t b);
fixed_t vector2_length_squared(vector2_t v);
fixed_t vector2_length(vector2_t v);
vector2_t vector2_normalize(vector2_t v);
fixed_t vector2_angle(vector2_t a, vector2_t b);

/* Vector3 function prototypes */
vector3_t vector3_init(fixed_t x, fixed_t y, fixed_t z);
vector3_t vector3_init_int(int x, int y, int z);
vector3_t vector3_add(vector3_t a, vector3_t b);
vector3_t vector3_sub(vector3_t a, vector3_t b);
vector3_t vector3_scale(vector3_t v, fixed_t s);
fixed_t vector3_dot(vector3_t a, vector3_t b);
vector3_t vector3_cross(vector3_t a, vector3_t b);
fixed_t vector3_length_squared(vector3_t v);
fixed_t vector3_length(vector3_t v);
vector3_t vector3_normalize(vector3_t v);
fixed_t vector3_angle(vector3_t a, vector3_t b);

/* Vector4 function prototypes */
vector4_t vector4_init(fixed_t x, fixed_t y, fixed_t z, fixed_t w);
vector4_t vector4_init_int(int x, int y, int z, int w);
vector4_t vector4_from_vec3(vector3_t v, fixed_t w);
vector4_t vector4_add(vector4_t a, vector4_t b);
vector4_t vector4_sub(vector4_t a, vector4_t b);
vector4_t vector4_scale(vector4_t v, fixed_t s);
fixed_t vector4_dot(vector4_t a, vector4_t b);
fixed_t vector4_length_squared(vector4_t v);
fixed_t vector4_length(vector4_t v);
vector4_t vector4_normalize(vector4_t v);

#endif /* VECTOR_H */
