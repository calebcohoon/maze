/*
 * fixed.c
 *
 * Implementation of 16.16 fixed-point number system
 */

#include "..\include\fixed.h"

/*
 * fixed_from_int: Convert integer to fixed-point number
 *
 * Parameters:
 *   n - Integer value to convert
 *
 * Returns:
 *   Fixed-point representation of the integer
 *
 * Notes:
 *   - Shifts the integer left by FIXED_SHIFT (16) bits
 *   - Same as multiplying by 2^16
 */
fixed_t fixed_from_int(int n) {
    return (fixed_t) n << FIXED_SHIFT;
}

/*
 * fixed_to_int: Convert fixed-point to integer (truncates)
 *
 * Parameters:
 *   x - Fixed-point value to convert
 *
 * Returns:
 *   Integer part of the fixed-point number
 *
 * Notes:
 *   - Shifts right by FIXED_SHIFT (16) bits to remove fractional part
 *   - Truncates towards zero
 */
int fixed_to_int(fixed_t x) {
    return (int) (x >> FIXED_SHIFT);
}

/*
 * fixed_from_float: Convert float to fixed-point
 *
 * Parameters:
 *   f - Float value to convert
 *
 * Returns:
 *   Fixed-point representation of the float
 *
 * Notes:
 *   - Multiplies by 2^16 and rounds to nearest fixed-point value
 *   - Use with caution in final build as floating-point may not be available
 */
fixed_t fixed_from_float(float f) {
    return (fixed_t) (f * (float) FIXED_ONE + (f >= 0 ? 0.5f : -0.5f));
}

/*
 * fixed_to_float: Convert fixed-point to float
 *
 * Parameters:
 *   x - Fixed-point value to convert
 *
 * Returns:
 *   Float representation of the fixed-point number
 *
 * Notes:
 *   - Divides by 2^16 to convert to floating-point
 *   - Use with caution in final build as floating-point may not be available
 */
float fixed_to_float(fixed_t x) {
    return (float) x / (float) FIXED_ONE;
}

/*
 * fixed_add: Add two fixed-point numbers
 *
 * Parameters:
 *   a, b - Fixed-point values to add
 *
 * Returns:
 *   Result of a + b
 *
 * Notes:
 *   - Direct integer addition works because fixed-point numbers
 *     have the same scaling factor (2^16)
 *   - No adjustment needed after addition
 */
fixed_t fixed_add(fixed_t a, fixed_t b) {
    return a + b;
}

/*
 * fixed_sub: Subtract two fixed-point numbers
 *
 * Parameters:
 *   a, b - Fixed-point values to subtract
 *
 * Returns:
 *   Result of a - b
 *
 * Notes:
 *   - Direct integer subtraction works because fixed-point numbers
 *     have the same scaling factor (2^16)
 *   - No adjustment needed after subtraction
 */
fixed_t fixed_sub(fixed_t a, fixed_t b) {
    return a - b;
}
