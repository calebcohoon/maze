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

/* Function prototype */
matrix_t matrix_init(void);      // Initialize to zero matrix
matrix_t matrix_identity(void);  // Initialize to identity matrix
void matrix_set(matrix_t *mat, int row, int col, fixed_t value);
fixed_t matrix_get(const matrix_t *mat, int row, int col);
int matrix_is_identity(const matrix_t *mat);
int matrix_equals(const matrix_t *a, const matrix_t *b);
void matrix_print(const matrix_t *mat);  // Debug function

#endif /* MATRIX_H */
