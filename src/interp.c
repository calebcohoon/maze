/*
 * interp.c
 *
 * Implementation of interpolation functions
 */

#include "..\include\interp.h"

#include "..\include\trig.h"

/*
 * linear_interp: Linear interpolation between two values
 *
 * Parameters:
 *   a - First value in fixed-point format
 *   b - Second value in fixed-point format
 *   t - Interpolation factor (0.0 to 1.0) in fixed-point format
 */
fixed_t linear_interp(fixed_t a, fixed_t b, fixed_t t) {
    fixed_t delta;

    /* Clamp t to [0,1] range */
    if (t < FIXED_ZERO) {
        t = FIXED_ZERO;
    } else if (t > FIXED_ONE) {
        t = FIXED_ONE;
    }

    /* Calculate a + t * (b - a) */
    delta = fixed_sub(b, a);
    return fixed_add(a, fixed_mul(t, delta));
}
