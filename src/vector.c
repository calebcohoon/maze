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
