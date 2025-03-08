/*
 * matrix.h
 *
 * 4x4 matrix operations for 3D transformations
 * Uses fixed-point arithmetic for performance on 486 systems
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "fixed.h"
#include "vector.h"

/* Type definitions */
typedef struct {
    fixed_t m[4][4];
} matrix_t;

/* Function prototypes */
matrix_t matrix_init(void);      // Initialize to zero matrix
matrix_t matrix_identity(void);  // Initialize to identity matrix
void matrix_set(matrix_t *mat, int row, int col, fixed_t value);
fixed_t matrix_get(const matrix_t *mat, int row, int col);
matrix_t matrix_add(const matrix_t *a, const matrix_t *b);
matrix_t matrix_sub(const matrix_t *a, const matrix_t *b);
matrix_t matrix_scale(const matrix_t *m, fixed_t scalar);
vector4_t matrix_mul_vector4(const matrix_t *m, const vector4_t *v);
vector3_t matrix_mul_vector3(const matrix_t *m, const vector3_t *v);
matrix_t matrix_mul(const matrix_t *a, const matrix_t *b);
matrix_t matrix_translation(fixed_t x, fixed_t y, fixed_t z);
matrix_t matrix_scaling(fixed_t x, fixed_t y, fixed_t z);
matrix_t matrix_rotation_x(unsigned char angle);
matrix_t matrix_rotation_y(unsigned char angle);
int matrix_is_identity(const matrix_t *mat);
int matrix_equals(const matrix_t *a, const matrix_t *b);
void matrix_print(const matrix_t *mat);  // Debug function

#endif /* MATRIX_H */
