/*
 * trig.c
 *
 * Implementation of trigonometric functions using lookup tables
 */

#include "..\include\trig.h"

#include <math.h>

/* Sine lookup table contains 256 values for full 360 degrees */
static fixed_t sine_table[TRIG_TABLE_SIZE];

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

    for (i = 0; i < TRIG_TABLE_SIZE; i++) {
        /* Calculate angle in radians */
        angle = i * angle_step;

        /* Calculate sine value and convert to fixed-point */
        sine_table[i] = fixed_from_float((float) sin(angle));
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
 * trig_get_table: Get pointer to the sine table
 *
 * Returns:
 *   Pointer to the sine lookup table
 */
const fixed_t *trig_get_table(void) {
    return sine_table;
}
