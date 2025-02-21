/*
 * vector.c
 *
 * Implementation of vector mathematics operations
 */

#include "..\include\vector.h"

/* Vector2 implementations */
vector2_t vector2_init(fixed_t x, fixed_t y) {
    vector2_t result;

    result.x = x;
    result.y = y;

    return result;
}

vector2_t vector2_init_int(int x, int y) {
    vector2_t result;

    result.x = fixed_from_int(x);
    result.y = fixed_from_int(y);

    return result;
}

/* Vector3 implementations */
vector3_t vector3_init(fixed_t x, fixed_t y, fixed_t z) {
    vector3_t result;

    result.x = x;
    result.y = y;
    result.z = z;

    return result;
}

vector3_t vector3_init_int(int x, int y, int z) {
    vector3_t result;

    result.x = fixed_from_int(x);
    result.y = fixed_from_int(y);
    result.z = fixed_from_int(z);

    return result;
}

/* Vector4 implementations */
vector4_t vector4_init(fixed_t x, fixed_t y, fixed_t z, fixed_t w) {
    vector4_t result;

    result.x = x;
    result.y = y;
    result.z = z;
    result.w = w;

    return result;
}

vector4_t vector4_init_int(int x, int y, int z, int w) {
    vector4_t result;

    result.x = fixed_from_int(x);
    result.y = fixed_from_int(y);
    result.z = fixed_from_int(z);
    result.w = fixed_from_int(w);

    return result;
}

vector4_t vector4_from_vec3(vector3_t v, fixed_t w) {
    vector4_t result;

    result.x = v.x;
    result.y = v.y;
    result.z = v.z;
    result.w = w;

    return result;
}
