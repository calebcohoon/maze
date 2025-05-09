/*
 * trig.c
 *
 * Implementation of trigonometric functions using lookup tables
 */

#include "..\include\trig.h"

#include <math.h>

/* Sine lookup table contains 256 values for full 360 degrees */
static fixed_t sine_table[TRIG_TABLE_SIZE];

/* Tangent lookup table contains 256 values for full 360 degrees */
static fixed_t tangent_table[TRIG_TABLE_SIZE];

/*
 * trig_init: Initialize the trigonometry lookup tables
 *
 * Calculates and fills the sine lookup table with fixed-point values
 * Uses floating-point math for initialization only
 */
void trig_init(void) {
    int i;
    double angle;
    double angle_step = (2.0 * 3.141592) / TRIG_TABLE_SIZE;
    double sin_value, cos_value, tan_value;

    for (i = 0; i < TRIG_TABLE_SIZE; i++) {
        /* Calculate angle in radians */
        angle = i * angle_step;

        /* Calculate sine value and convert to fixed-point */
        sin_value = sin(angle);
        sine_table[i] = fixed_from_float((float) sin_value);

        /* Calculate tangent value and convert to fixed-point */
        cos_value = cos(angle);

        /* Handle special cases for tangent near 90 deg and 270 deg */
        if (fabs(cos_value) < 0.0001) {
            /* Tangent is undefined */
            tangent_table[i] = TRIG_TAN_INVALID;
        } else {
            /* Calculate tangent safely */
            tan_value = sin_value / cos_value;

            /* Clamp very large values to avoid fixed-point overflow */
            if (tan_value > 32767.0) {
                tangent_table[i] = FIXED_MAX;
            } else if (tan_value < -32768.0) {
                tangent_table[i] = FIXED_MIN;
            } else {
                tangent_table[i] = fixed_from_float((float) tan_value);
            }
        }
    }
}

/*
 * trig_sine: Get sine value from the lookup table
 *
 * Parameters:
 *   angle - Angle value 0-255 representing 0-359 degrees
 *
 * Returns:
 *   Sine value in fixed-point format
 *
 * Notes:
 *   - No range checking needed since unsigned char wraps automatically
 */
fixed_t trig_sine(unsigned char angle) {
    return sine_table[angle];
}

/*
 * trig_cosine: Get cosine value from the lookup table
 *
 * Parameters:
 *   angle - Angle value 0-255 representing 0-359 degrees
 *
 * Returns:
 *   Cosine value in fixed-point format
 *
 * Notes:
 *   - Cosine is equivalent to sine(angle + 64)
 *   - No range checking needed since unsigned char wraps automatically
 */
fixed_t trig_cosine(unsigned char angle) {
    return sine_table[(angle + 64) % TRIG_TABLE_SIZE];
}

/*
 * trig_tangent: Get tangent value from the lookup table
 *
 * Parameters:
 *   angle - Angle value 0-255 representing 0-359 degrees
 *
 * Returns:
 *   Tangent value in fixed-point format
 *
 * Notes:
 *   - TRIG_TAN_INVALID will be returned for undefined tangent values
 */
fixed_t trig_tangent(unsigned char angle) {
    return tangent_table[angle];
}

/*
 * trig_arccos: Calculate the inverse of the cosine of a fixed-point value
 *
 * Parameters:
 *   x - Cosine value in fixed-point format in range [-1, 1]
 *
 * Returns:
 *   Angle in radians as a fixed-point number
 *   Returns 0 if input is out of range
 */
fixed_t trig_arccos(fixed_t x) {
    int i;
    fixed_t closest_diff = FIXED_MAX;
    int closest_index = 0;
    fixed_t cos_val, diff;

    /* Check if input is within valid range */
    if (x < -FIXED_ONE || x > FIXED_ONE) {
        return 0;
    }

    /* Special cases for exact values */
    if (x == FIXED_ONE) {
        return 0;
    }

    if (x == FIXED_ZERO) {
        return fixed_div(FIXED_PI, fixed_from_int(2));
    }

    if (x == -FIXED_ONE) {
        return FIXED_PI;
    }

    /* Scan through the cosine table to find the closest value */
    for (i = 0; i < TRIG_TABLE_SIZE - 1; i++) {
        /* Get the cosine value at this angle */
        cos_val = sine_table[(i + 64) % TRIG_TABLE_SIZE];

        /* Calculate the distance to our target value */
        diff = fixed_abs(fixed_sub(cos_val, x));

        /* If this is closer than our previous best match */
        if (diff < closest_diff) {
            closest_diff = diff;
            closest_index = i;
        }
    }

    /* Convert the angle from table index to radians */
    return fixed_mul(fixed_from_int(closest_index), fixed_div(FIXED_PI, fixed_from_int(128)));
}

/*
 * trig_get_sine_table: Get pointer to the sine table
 *
 * Returns:
 *   Pointer to the sine lookup table
 */
const fixed_t *trig_get_sine_table(void) {
    return sine_table;
}

/*
 * trig_get_tangent_table: Get pointer to the tangent table
 *
 * Returns:
 *   Pointer to the tangent lookup table
 */
const fixed_t *trig_get_tangent_table(void) {
    return tangent_table;
}
