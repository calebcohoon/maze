/*
 * vector.c
 *
 * Implementation of vector mathematics operations
 */

#include "..\include\vector.h"

/*
 * vector2_init: Initialize a 2D vector with given components
 *
 * Parameters:
 *   x - X component in fixed-point format
 *   y - Y component in fixed-point format
 *
 * Returns:
 *   Initialized 2D vector
 */
vector2_t vector2_init(fixed_t x, fixed_t y) {
    vector2_t result;

    result.x = x;
    result.y = y;

    return result;
}

/*
 * vector2_init_int: Initialize a 2D vector with integer components
 *
 * Parameters:
 *   x - X component as integer
 *   y - Y component as integer
 *
 * Returns:
 *   Initialized 2D vector with components converted to fixed-point
 */
vector2_t vector2_init_int(int x, int y) {
    vector2_t result;

    result.x = fixed_from_int(x);
    result.y = fixed_from_int(y);

    return result;
}

/*
 * vector2_add: Adds two 2D vectors together
 *
 * Parameters:
 *   a - First vector
 *   b - Second vector
 *
 * Returns:
 *   The result of a + b
 */
vector2_t vector2_add(vector2_t a, vector2_t b) {
    vector2_t result;

    result.x = fixed_add(a.x, b.x);
    result.y = fixed_add(a.y, b.y);

    return result;
}

/*
 * vector2_sub: Subtracts two 2D vectors
 *
 * Parameters:
 *   a - First vector
 *   b - Second vector
 *
 * Returns:
 *   The result of a - b
 */
vector2_t vector2_sub(vector2_t a, vector2_t b) {
    vector2_t result;

    result.x = fixed_sub(a.x, b.x);
    result.y = fixed_sub(a.y, b.y);

    return result;
}

/*
 * vector2_scale: Multiply a 2D vector by a scalar
 *
 * Parameters:
 *   v - Vector to scale
 *   s - Scalar in fixed-point format
 *
 * Returns:
 *   The result of (v.x * s, v.y * s)
 */
vector2_t vector2_scale(vector2_t v, fixed_t s) {
    vector2_t result;

    result.x = fixed_mul(v.x, s);
    result.y = fixed_mul(v.y, s);

    return result;
}

/*
 * vector2_dot: Calculate dot product of two 2D vectors
 *
 * Parameters:
 *   a - First vector
 *   b - Second vector
 *
 * Returns:
 *   The dot product of a dot b
 */
fixed_t vector2_dot(vector2_t a, vector2_t b) {
    fixed_t x_prod = fixed_mul(a.x, b.x);
    fixed_t y_prod = fixed_mul(a.y, b.y);

    return fixed_add(x_prod, y_prod);
}

/*
 * vector2_length_squared: Calculate squared length of a 2D vector
 *
 * Parameters:
 *   v - Vector to calculate squared length of
 *
 * Returns:
 *   Squared length of the vector in fixed-point format
 *
 * Notes:
 *   - More efficient than calculating actual length when only comparing distances
 */
fixed_t vector2_length_squared(vector2_t v) {
    return vector2_dot(v, v);
}

/*
 * vector2_length: Calculate length of a 2D vector
 *
 * Parameters:
 *   v - Vector to calculate length of
 *
 * Returns:
 *   Length of the vector in fixed-point format
 */
fixed_t vector2_length(vector2_t v) {
    return fixed_sqrt(vector2_length_squared(v));
}

/*
 * vector2_normalize: Create a unit vector in the same direction
 *
 * Parameters:
 *   v - Vector to normalize
 *
 * Returns:
 *   Normalized vector with length 1 in the same direction
 */
vector2_t vector2_normalize(vector2_t v) {
    vector2_t result;
    fixed_t length = vector2_length(v);

    /* Avoid division by zero */
    if (length == 0) {
        return vector2_init(FIXED_ZERO, FIXED_ZERO);
    }

    /* Divide each component by the length */
    result.x = fixed_div(v.x, length);
    result.y = fixed_div(v.y, length);

    return result;
}

/*
 * vector3_init: Initialize a 3D vector with given components
 *
 * Parameters:
 *   x - X component in fixed-point format
 *   y - Y component in fixed-point format
 *   z - Z component in fixed-point format
 *
 * Returns:
 *   Initialized 3D vector
 */
vector3_t vector3_init(fixed_t x, fixed_t y, fixed_t z) {
    vector3_t result;

    result.x = x;
    result.y = y;
    result.z = z;

    return result;
}

/*
 * vector3_init_int: Initialize a 3D vector with integer components
 *
 * Parameters:
 *   x - X component as integer
 *   y - Y component as integer
 *   z - Z component as integer
 *
 * Returns:
 *   Initialized 3D vector with components converted to fixed-point
 */
vector3_t vector3_init_int(int x, int y, int z) {
    vector3_t result;

    result.x = fixed_from_int(x);
    result.y = fixed_from_int(y);
    result.z = fixed_from_int(z);

    return result;
}

/*
 * vector3_add: Adds two 3D vectors together
 *
 * Parameters:
 *   a - First vector
 *   b - Second vector
 *
 * Returns:
 *   The result of a + b
 */
vector3_t vector3_add(vector3_t a, vector3_t b) {
    vector3_t result;

    result.x = fixed_add(a.x, b.x);
    result.y = fixed_add(a.y, b.y);
    result.z = fixed_add(a.z, b.z);

    return result;
}

/*
 * vector3_sub: Subtracts two 3D vectors
 *
 * Parameters:
 *   a - First vector
 *   b - Second vector
 *
 * Returns:
 *   The result of a - b
 */
vector3_t vector3_sub(vector3_t a, vector3_t b) {
    vector3_t result;

    result.x = fixed_sub(a.x, b.x);
    result.y = fixed_sub(a.y, b.y);
    result.z = fixed_sub(a.z, b.z);

    return result;
}

/*
 * vector3_scale: Multiply a 3D vector by a scalar
 *
 * Parameters:
 *   v - Vector to scale
 *   s - Scalar in fixed-point format
 *
 * Returns:
 *   The result of (v.x * s, v.y * s, v.z * s)
 */
vector3_t vector3_scale(vector3_t v, fixed_t s) {
    vector3_t result;

    result.x = fixed_mul(v.x, s);
    result.y = fixed_mul(v.y, s);
    result.z = fixed_mul(v.z, s);

    return result;
}

/*
 * vector3_dot: Calculate dot product of two 3D vectors
 *
 * Parameters:
 *   a - First vector
 *   b - Second vector
 *
 * Returns:
 *   The dot product of a dot b
 */
fixed_t vector3_dot(vector3_t a, vector3_t b) {
    fixed_t x_prod = fixed_mul(a.x, b.x);
    fixed_t y_prod = fixed_mul(a.y, b.y);
    fixed_t z_prod = fixed_mul(a.z, b.z);

    return fixed_add(fixed_add(x_prod, y_prod), z_prod);
}

/*
 * vector3_cross: Calculate cross product of two 3D vectors
 *
 * Parameters:
 *   a - First vector
 *   b - Second vector
 *
 * Returns:
 *   The cross product, a vector perpendicular to both a and b
 */
vector3_t vector3_cross(vector3_t a, vector3_t b) {
    vector3_t result;

    /* Calculate components using the cross product formula */
    result.x = fixed_sub(fixed_mul(a.y, b.z), fixed_mul(a.z, b.y));
    result.y = fixed_sub(fixed_mul(a.z, b.x), fixed_mul(a.x, b.z));
    result.z = fixed_sub(fixed_mul(a.x, b.y), fixed_mul(a.y, b.x));

    return result;
}

/*
 * vector3_length_squared: Calculate squared length of a 3D vector
 *
 * Parameters:
 *   v - Vector to calculate squared length of
 *
 * Returns:
 *   Squared length of the vector in fixed-point format
 */
fixed_t vector3_length_squared(vector3_t v) {
    return vector3_dot(v, v);
}

/*
 * vector3_length: Calculate length of a 3D vector
 *
 * Parameters:
 *   v - Vector to calculate length of
 *
 * Returns:
 *   Length of the vector in fixed-point format
 */
fixed_t vector3_length(vector3_t v) {
    return fixed_sqrt(vector3_length_squared(v));
}

/*
 * vector3_normalize: Create a unit vector in the same direction
 *
 * Parameters:
 *   v - Vector to normalize
 *
 * Returns:
 *   Normalized vector with length 1 in the same direction
 */
vector3_t vector3_normalize(vector3_t v) {
    vector3_t result;
    fixed_t length = vector3_length(v);

    /* Avoid division by zero */
    if (length == 0) {
        return vector3_init(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);
    }

    /* Divide each component by the length */
    result.x = fixed_div(v.x, length);
    result.y = fixed_div(v.y, length);
    result.z = fixed_div(v.z, length);

    return result;
}

/*
 * vector4_init: Initialize a 4D vector with given components
 *
 * Parameters:
 *   x - X component in fixed-point format
 *   y - Y component in fixed-point format
 *   z - Z component in fixed-point format
 *   w - W component in fixed-point format
 *
 * Returns:
 *   Initialized 4D vector
 */
vector4_t vector4_init(fixed_t x, fixed_t y, fixed_t z, fixed_t w) {
    vector4_t result;

    result.x = x;
    result.y = y;
    result.z = z;
    result.w = w;

    return result;
}

/*
 * vector4_init_int: Initialize a 4D vector with integer components
 *
 * Parameters:
 *   x - X component as integer
 *   y - Y component as integer
 *   z - Z component as integer
 *   w - W component as integer
 *
 * Returns:
 *   Initialized 4D vector with components converted to fixed-point
 */
vector4_t vector4_init_int(int x, int y, int z, int w) {
    vector4_t result;

    result.x = fixed_from_int(x);
    result.y = fixed_from_int(y);
    result.z = fixed_from_int(z);
    result.w = fixed_from_int(w);

    return result;
}

/*
 * vector4_from_vec3: Create a 4D vector from a 3D vector
 *
 * Parameters:
 *   v - Source 3D vector
 *   w - W component in fixed-point format
 *
 * Returns:
 *   4D vector with components from 3D vector and specified W
 */
vector4_t vector4_from_vec3(vector3_t v, fixed_t w) {
    vector4_t result;

    result.x = v.x;
    result.y = v.y;
    result.z = v.z;
    result.w = w;

    return result;
}

/*
 * vector4_add: Adds two 4D vectors together
 *
 * Parameters:
 *   a - First vector
 *   b - Second vector
 *
 * Returns:
 *   The result of a + b
 */
vector4_t vector4_add(vector4_t a, vector4_t b) {
    vector4_t result;

    result.x = fixed_add(a.x, b.x);
    result.y = fixed_add(a.y, b.y);
    result.z = fixed_add(a.z, b.z);
    result.w = fixed_add(a.w, b.w);

    return result;
}

/*
 * vector4_sub: Subtracts two 4D vectors
 *
 * Parameters:
 *   a - First vector
 *   b - Second vector
 *
 * Returns:
 *   The result of a - b
 */
vector4_t vector4_sub(vector4_t a, vector4_t b) {
    vector4_t result;

    result.x = fixed_sub(a.x, b.x);
    result.y = fixed_sub(a.y, b.y);
    result.z = fixed_sub(a.z, b.z);
    result.w = fixed_sub(a.w, b.w);

    return result;
}

/*
 * vector4_scale: Multiply a 4D vector by a scalar
 *
 * Parameters:
 *   v - Vector to scale
 *   s - Scalar in fixed-point format
 *
 * Returns:
 *   The result of (v.x * s, v.y * s, v.z * s, v.w * z)
 */
vector4_t vector4_scale(vector4_t v, fixed_t s) {
    vector4_t result;

    result.x = fixed_mul(v.x, s);
    result.y = fixed_mul(v.y, s);
    result.z = fixed_mul(v.z, s);
    result.w = fixed_mul(v.w, s);

    return result;
}

/*
 * vector4_dot: Calculate dot product of two 4D vectors
 *
 * Parameters:
 *   a - First vector
 *   b - Second vector
 *
 * Returns:
 *   The dot product of a dot b
 */
fixed_t vector4_dot(vector4_t a, vector4_t b) {
    fixed_t x_prod = fixed_mul(a.x, b.x);
    fixed_t y_prod = fixed_mul(a.y, b.y);
    fixed_t z_prod = fixed_mul(a.z, b.z);
    fixed_t w_prod = fixed_mul(a.w, b.w);

    return fixed_add(fixed_add(fixed_add(x_prod, y_prod), z_prod), w_prod);
}

/*
 * vector4_length_squared: Calculate squared length of a 4D vector
 *
 * Parameters:
 *   v - Vector to calculate squared length of
 *
 * Returns:
 *   Squared length of the vector in fixed-point format
 */
fixed_t vector4_length_squared(vector4_t v) {
    return vector4_dot(v, v);
}

/*
 * vector4_length: Calculate length of a 4D vector
 *
 * Parameters:
 *   v - Vector to calculate length of
 *
 * Returns:
 *   Length of the vector in fixed-point format
 */
fixed_t vector4_length(vector4_t v) {
    return fixed_sqrt(vector4_length_squared(v));
}

/*
 * vector4_normalize: Create a unit vector in the same direction
 *
 * Parameters:
 *   v - Vector to normalize
 *
 * Returns:
 *   Normalized vector with length 1 in the same direction
 */
vector4_t vector4_normalize(vector4_t v) {
    vector4_t result;
    fixed_t length = vector4_length(v);

    /* Avoid division by zero */
    if (length == 0) {
        return vector4_init(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);
    }

    /* Divide each component by the length */
    result.x = fixed_div(v.x, length);
    result.y = fixed_div(v.y, length);
    result.z = fixed_div(v.z, length);
    result.w = fixed_div(v.w, length);

    return result;
}
