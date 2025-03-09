/*
 * interp.h
 *
 * Interpolation functions for smooth transitions
 * Provides functions for working with values between discrete steps
 */

#ifndef INTERP_H
#define INTERP_H

#include "fixed.h"

/* Function prototypes */
fixed_t linear_interp(fixed_t a, fixed_t b, fixed_t t);

#endif /* INTERP_H */
