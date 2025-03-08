/*
 * trig.h
 *
 * Trigonometric functions using lookup tables
 * Provides efficient sine, cosine and tangent calculation
 * for 3D rotations and transformations
 */

#ifndef TRIG_H
#define TRIG_H

#include "fixed.h"

/* Constants */
#define TRIG_TABLE_SIZE  256
#define TRIG_ANGLE_MAX   256
#define TRIG_TAN_INVALID 0x7FFFFFFF

/* Function prototypes */
void trig_init();
fixed_t trig_sine(unsigned char angle);
fixed_t trig_cosine(unsigned char angle);
fixed_t trig_tangent(unsigned char angle);
const fixed_t *trig_get_sine_table(void);
const fixed_t *trig_get_tangent_table(void);

#endif /* TRIG_H */
