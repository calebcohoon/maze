/*
 * matrix.c
 *
 * Implementation of 4x4 matrix operations for 3D transformations
 */

#include "..\include\matrix.h"

#include <stdio.h>

/*
 * matrix_init: Initialize a matrix with all zeros
 *
 * Returns:
 *   A zero-initialized matrix
 */
matrix_t matrix_init(void) {
    matrix_t result;
    int row, col;

    /* Initialize all elements to zero */
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            result.m[row][col] = FIXED_ZERO;
        }
    }

    return result;
}

/*
 * matrix_identity: Initialize a matrix as identity matrix
 *
 * Returns:
 *   An identity matrix where diagonal elements are 1 and all others are 0
 */
matrix_t matrix_identity(void) {
    matrix_t result;
    int row, col;

    /* Initialize all elements to zero */
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            if (row == col) {
                /* Diagonal element */
                result.m[row][col] = FIXED_ONE;
            } else {
                result.m[row][col] = FIXED_ZERO;
            }
        }
    }

    return result;
}

/*
 * matrix_set: Set a specific element in a matrix
 *
 * Parameters:
 *   mat - Pointer to the matrix to modify
 *   row - Row index (0-3)
 *   col - Column index (0-3)
 *   value - Fixed-point value to set
 */
void matrix_set(matrix_t *mat, int row, int col, fixed_t value) {
    /* Bounds check to prevent buffer overflows */
    if (row >= 0 && row < 4 && col >= 0 && col < 4) {
        mat->m[row][col] = value;
    }
}

/*
 * matrix_get: Get a specific element from a matrix
 *
 * Parameters:
 *   mat - Pointer to the matrix to read from
 *   row - Row index (0-3)
 *   col - Column index (0-3)
 *
 * Returns:
 *   The fixed-point value at the specified position
 */
fixed_t matrix_get(const matrix_t *mat, int row, int col) {
    /* Bounds check to prevent buffer overflows */
    if (row >= 0 && row < 4 && col >= 0 && col < 4) {
        return mat->m[row][col];
    }

    return FIXED_ZERO;
}

/*
 * matrix_add: Add two matrices element wise
 *
 * Parameters:
 *   a - Pointer to the first matrix
 *   b - Pointer to the second matrix
 *
 * Returns:
 *   The result of a + b
 */
matrix_t matrix_add(const matrix_t *a, const matrix_t *b) {
    matrix_t result;
    int row, col;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            result.m[row][col] = fixed_add(a->m[row][col], b->m[row][col]);
        }
    }

    return result;
}

/*
 * matrix_sub: Subtract two matrices element wise
 *
 * Parameters:
 *   a - Pointer to the first matrix
 *   b - Pointer to the second matrix
 *
 * Returns:
 *   The result of a - b
 */
matrix_t matrix_sub(const matrix_t *a, const matrix_t *b) {
    matrix_t result;
    int row, col;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            result.m[row][col] = fixed_sub(a->m[row][col], b->m[row][col]);
        }
    }

    return result;
}

/*
 * matrix_scale: Multiply all elements of a matrix by a scalar
 *
 * Parameters:
 *   m - Pointer to the matrix
 *   scalar - Fixed-point scalar to multiply by
 *
 * Returns:
 *   The result of scaling each element of the matrix
 */
matrix_t matrix_scale(const matrix_t *m, fixed_t scalar) {
    matrix_t result;
    int row, col;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            result.m[row][col] = fixed_mul(m->m[row][col], scalar);
        }
    }

    return result;
}

/*
 * matrix_mul_vector4: Multiply a 4x4 matrix by a 4D vector
 *
 * Parameters:
 *   m - Pointer to the matrix
 *   v - Pointer to the 4D vector
 *
 * Returns:
 *   The resulting 4D vector
 */
vector4_t matrix_mul_vector4(const matrix_t *m, const vector4_t *v) {
    vector4_t result;
    int i, j;

    for (i = 0; i < 4; i++) {
        result.v[i] = FIXED_ZERO;

        for (j = 0; j < 4; j++) {
            result.v[i] = fixed_add(result.v[i], fixed_mul(m->m[i][j], v->v[j]));
        }
    }

    return result;
}

/*
 * matrix_mul_vector3: Multiply a 4x4 matrix by a 3D vector
 *
 * Parameters:
 *   m - Pointer to the matrix
 *   v - Pointer to the 3D vector
 *
 * Returns:
 *   The resulting 3D vector
 */
vector3_t matrix_mul_vector3(const matrix_t *m, const vector3_t *v) {
    vector3_t result;
    int i, j;

    for (i = 0; i < 3; i++) {
        result.v[i] = m->m[i][3];

        for (j = 0; j < 3; j++) {
            result.v[i] = fixed_add(result.v[i], fixed_mul(m->m[i][j], v->v[j]));
        }
    }

    return result;
}

/*
 * matrix_mul: Multiply two 4x4 matrices
 *
 * Parameters:
 *   a - Pointer to the first matrix
 *   b - Pointer to the second matrix
 *
 * Returns:
 *   The result of a * b
 */
matrix_t matrix_mul(const matrix_t *a, const matrix_t *b) {
    matrix_t result;
    int i, j, k;
    fixed_t sum;

    /* Compute each element of the result matrix */
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            /* Calculate dot product of row i from a and column j from b */
            sum = FIXED_ZERO;

            for (k = 0; k < 4; k++) {
                sum = fixed_add(sum, fixed_mul(a->m[i][k], b->m[k][j]));
            }

            result.m[i][j] = sum;
        }
    }

    return result;
}

/*
 * matrix_translation: Create a translation matrix
 *
 * Parameters:
 *   x - Translation along the X axis in fixed-point format
 *   y - Translation along the Y axis in fixed-point format
 *   z - Translation along the Z axis in fixed-point format
 *
 * Returns:
 *   A 4x4 matrix translated by the specified amounts
 */
matrix_t matrix_translation(fixed_t x, fixed_t y, fixed_t z) {
    matrix_t result = matrix_identity();

    /* Set translation components in the rightmost column */
    result.m[0][3] = x;
    result.m[1][3] = y;
    result.m[2][3] = z;

    return result;
}

/*
 * matrix_is_identity: Check if a matrix is an identity matrix
 *
 * Parameters:
 *   mat - Pointer to the matrix to check
 *
 * Returns:
 *   1 if the matrix is an identity matrix, 0 otherwise
 */
int matrix_is_identity(const matrix_t *mat) {
    int row, col;
    fixed_t expected;
    fixed_t epsilon = 5; /* Approx 0.000076 in fixed-point */

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            /* Expected value: 1 on diagonal, 0 elsewhere */
            expected = (row == col) ? FIXED_ONE : FIXED_ZERO;

            /* Check against a small epsilon to account for floating point precision */
            if (fixed_abs(mat->m[row][col] - expected) > epsilon) {
                return 0;  // Not identity
            }
        }
    }

    return 1;  // Must be an identity matrix
}

/*
 * matrix_equals: Check if two matrices are equal
 *
 * Parameters:
 *   a - Pointer to the first matrix
 *   b - Pointer to the second matrix
 *
 * Returns:
 *   1 if the matrices are equal, 0 otherwise
 */
int matrix_equals(const matrix_t *a, const matrix_t *b) {
    int row, col;
    fixed_t epsilon = 5; /* Approx 0.000076 in fixed-point */

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            /* Check against a small epsilon to account for floating point precision */
            if (fixed_abs(a->m[row][col] - b->m[row][col]) > epsilon) {
                return 0;  // Not identical
            }
        }
    }

    return 1;  // All elements are equal
}

/*
 * matrix_print: Print matrix values to console for debugging
 *
 * Parameters:
 *   mat - Pointer to the matrix to print
 */
void matrix_print(const matrix_t *mat) {
    int row, col;

    printf("Matrix:\n");

    for (row = 0; row < 4; row++) {
        printf("[");

        for (col = 0; col < 4; col++) {
            printf("%8.4f", fixed_to_float(mat->m[row][col]));

            if (col < 3) {
                printf(", ");
            }
        }

        printf("]\n");
    }
}
