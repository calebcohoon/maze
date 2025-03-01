/*
 * fixed.c
 *
 * Implementation of 16.16 fixed-point number system
 */

#include "..\include\fixed.h"

/* Number of entries in the trig lookup table */
#define TRIG_TABLE_SIZE 13

/*
 * Trigonometric lookup table
 */
static const fixed_t trig_table[TRIG_TABLE_SIZE][2] = {
    {65536L, 0},         // cos(0)
    {63300L, 17170L},    // cos(15)
    {56756L, 34326L},    // cos(30)
    {46341L, 51472L},    // cos(45)
    {32768L, 68619L},    // cos(60)
    {16962L, 85765L},    // cos(75)
    {0L, 102944L},       // cos(90)
    {-16962L, 120123L},  // cos(105)
    {-32768L, 137270L},  // cos(120)
    {-46341L, 154417L},  // cos(135)
    {-56756L, 171563L},  // cos(150)
    {-63300L, 188710L},  // cos(165)
    {-65536L, 205887L}   // cos(180)
};

/*
 * fixed_from_int: Convert integer to fixed-point number
 *
 * Parameters:
 *   n - Integer value to convert
 *
 * Returns:
 *   Fixed-point representation of the integer
 */
fixed_t fixed_from_int(int n) {
    /* Check if input is too large or small */
    if (n > FIXED_MAX_INT) {
        return FIXED_MAX;
    }

    if (n < FIXED_MIN_INT) {
        return FIXED_MIN;
    }

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
 */
fixed_t fixed_sub(fixed_t a, fixed_t b) {
    return a - b;
}

/*
 * fixed_mul: Multiply two fixed-point numbers
 *
 * Parameters:
 *   a, b - Fixed-point values to multiply
 *
 * Returns:
 *   Result of a * b
 */
fixed_t fixed_mul(fixed_t a, fixed_t b) {
    fixed_t result;

    __asm {
        mov eax, a          ; Load first operand into eax
        imul b              ; Multiply by second operand, result in edx:eax
        shrd eax, edx, 16   ; Shift composite 64-bit value right by 16
        mov result, eax     ; Store the result
    }

    return result;
}

/*
 * fixed_div: Divide two fixed-point numbers
 *
 * Parameters:
 *   a - Dividend (fixed-point value)
 *   b - Divisor (fixed-point value)
 *
 * Returns:
 *   Result of a / b
 *   Returns FIXED_DIV_ZERO if b is zero
 */
fixed_t fixed_div(fixed_t a, fixed_t b) {
    fixed_t result;

    /* Check for division by zero */
    if (b == 0) {
        return FIXED_DIV_ZERO;
    }

    __asm {
        mov eax, a          ; Load dividend into eax
        cdq                 ; Sign extend eax into edx
        rol eax, 16         ; Rotate left to get into position
        mov dx, ax          ; Move lower 16-bits to dx
        xor ax, ax          ; Zero lower 16-bits
        idiv b              ; Divide edx:eax by divisor
        mov result, eax     ; Store result
    }

    return result;
}

/*
 * fixed_abs: Get absolute value of a fixed-point number
 *
 * Parameters:
 *   x - Number to remove the sign (fixed-point value)
 *
 * Returns:
 *   Result of |x|
 */
fixed_t fixed_abs(fixed_t x) {
    fixed_t result;

    __asm {
        mov eax, x          ; Load value into eax
        cdq                 ; Sign extend eax into edx (fills edx with sign bit)
        xor eax, edx        ; Flip bits if negative
        sub eax, edx        ; Add 1 if was negative
        mov result, eax     ; Store result
    }

    return result;
}

/*
 * fixed_sign: Get sign of a fixed-point number
 *
 * Parameters:
 *   x - Number to read the sign (fixed-point value)
 *
 * Returns:
 *   -1 if negative or 1 if positive or 0 if zero
 */
int fixed_sign(fixed_t x) {
    int result;

    __asm {
        xor eax, eax        ; Clear eax
        mov edx, x          ; Load value into edx
        test edx, edx       ; Test value
        jz done             ; If zero, leave eax as 0
        mov eax, 1          ; Assume positive
        js negative         ; Jump if sign bit is set
        jmp done            ; Positive case
    negative:
        mov eax, -1         ; Negative case
    done:
        mov result, eax     ; Store result
    }

    return result;
}

/*
 * fixed_is_neg: Check if fixed-point number is negative
 *
 * Parameters:
 *   x - Number to read the sign (fixed-point value)
 *
 * Returns:
 *   1 if negative or 0 if positive
 */
int fixed_is_neg(fixed_t x) {
    return (x < 0) ? 1 : 0;
}

/*
 * fixed_neg: Negate a fixed-point number
 *
 * Parameters:
 *   x - Number to negate (fixed-point value)
 *
 * Returns:
 *   Negated value of fixed-point number
 */
fixed_t fixed_neg(fixed_t x) {
    fixed_t result;

    __asm {
        mov eax, x          ; Load value into eax
        neg eax             ; Negate value
        mov result, eax     ; Store result
    }

    return result;
}

/*
 * fixed_sqrt: Calculate square root of a fixed-point number
 *
 * Parameters:
 *   x - Fixed-point value to find square root of (must be non-negative)
 *
 * Returns:
 *   Square root of x in fixed-point format
 *   Returns 0 if input is negative
 */
fixed_t fixed_sqrt(fixed_t x) {
    fixed_t result;

    /* Return 0 for negative inputs */
    if (x < 0) {
        return 0;
    }

    /* Handle 0 and 1 specially */
    if (x == 0 || x == FIXED_ONE) {
        return x;
    }

    __asm {
        mov ebx, x          ; Load input value into ebx
        mov eax, ebx        ; Initial guess = x/2
        shr eax, 1
        mov ecx, 6          ; Number of iterations

    newton_loop:
        push ecx            ; Save counter
        push eax            ; Save current guess

        ; Compute x/guess
        mov eax, ebx        ; Load x
        cdq                 ; Sign extend to edx:eax
        rol eax, 16         ; Adjust for fixed-point division
        mov dx, ax
        xor ax, ax
        pop ecx             ; Restore guess into divisor
        idiv ecx            ; Divide x by guess

        ; Add guess to x/guess
        add eax, ecx

        ; Divide by 2
        sar eax, 1

        pop ecx             ; Restore counter
        loop newton_loop

        mov result, eax
    }

    return result;
}

/*
 * fixed_arccos: Calculate the inverse of the cosine of a fixed-point value
 *
 * Parameters:
 *   x - Cosine value in fixed-point format in range [-1, 1]
 *
 * Returns:
 *   Angle in radians as a fixed-point number
 *   Returns 0 if input is out of range
 */
fixed_t fixed_arccos(fixed_t x) {
    fixed_t cos_lo, cos_hi, angle_lo, angle_hi;
    fixed_t numerator, denominator, t, angle_delta, angle_offset;
    int i;

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

    /* Find the right segment in the lookup table */
    for (i = 0; i < TRIG_TABLE_SIZE - 1; i++) {
        if (x >= trig_table[i + 1][0] && x <= trig_table[i][0]) {
            break;
        }
    }

    /* If we reach the end of the table, clamp to valid range */
    if (i >= TRIG_TABLE_SIZE - 1) {
        i = TRIG_TABLE_SIZE - 2;
    }

    /* Linear interpolation between adjacent table entries */
    cos_lo = trig_table[i + 1][0];
    cos_hi = trig_table[i][0];
    angle_lo = trig_table[i + 1][1];
    angle_hi = trig_table[i][1];

    /* t = (x - cos_lo) / (cos_hi - cos_lo) */
    numerator = fixed_sub(x, cos_lo);
    denominator = fixed_sub(cos_hi, cos_lo);

    /* Avoid division by zero */
    if (denominator == 0) {
        return angle_lo;
    }

    t = fixed_div(numerator, denominator);

    /* angle = angle_lo + t * (angle_hi - angle_lo) */
    angle_delta = fixed_sub(angle_hi, angle_lo);
    angle_offset = fixed_mul(t, angle_delta);

    return fixed_add(angle_lo, angle_offset);
}
