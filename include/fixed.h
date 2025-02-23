/*
 * fixed.h
 *
 * 16.16 fixed-point number system implementation
 * Uses 32-bit integers with 16 bits for the integer part
 * and 16 bits for the fractional part.
 */

#ifndef FIXED_H
#define FIXED_H

/* Type definitions */
typedef long fixed_t;

/* Constants */
#define FIXED_HALF     (1L << 15)                /* 0.5 in fixed-point */
#define FIXED_ONE      (1L << 16)                /* 1.0 in fixed-point */
#define FIXED_ZERO     0L                        /* 0.0 in fixed-point */
#define FIXED_PI       205887L                   /* PI in fixed-point (3.14159...) */
#define FIXED_SHIFT    16                        /* Number of fractional bits */
#define FIXED_DIV_ZERO ((fixed_t) 0x7FFFFFFF)    /* Error value for div by zero */
#define FIXED_MAX      ((fixed_t) 0x7FFF0000)    /* Maximum valid fixed-point value */
#define FIXED_MIN      ((fixed_t) (-0x80000000)) /* Minimum valid fixed-point value*/
#define FIXED_MAX_INT  32767                     /* Maximum valid integer component */
#define FIXED_MIN_INT  (-32768)                  /* Minimum valid integer component */

/* Function prototypes */
fixed_t fixed_from_int(int n);
int fixed_to_int(fixed_t x);
fixed_t fixed_from_float(float f);
float fixed_to_float(fixed_t x);
fixed_t fixed_add(fixed_t a, fixed_t b);
fixed_t fixed_sub(fixed_t a, fixed_t b);
fixed_t fixed_mul(fixed_t a, fixed_t b);
fixed_t fixed_div(fixed_t a, fixed_t b);
fixed_t fixed_abs(fixed_t x);
int fixed_sign(fixed_t x);
int fixed_is_neg(fixed_t x);
fixed_t fixed_neg(fixed_t x);
fixed_t fixed_sqrt(fixed_t x);

#endif /* FIXED_H */
