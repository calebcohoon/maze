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

/*
 * fixed_mul: Multiply two fixed-point numbers using 486 assembly
 *
 * Parameters:
 *   a, b - Fixed-point values to multiply
 *
 * Returns:
 *   Result of a * b
 *
 * Notes:
 *   - Uses IMUL instruction to get full 64-bit result, then
 *     shifts right by 16 to adjust back to fixed-point format
 *   - May overflow if result exceeds 32767.99998474121094
 *   - May underflow if result is less than -32768.0
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
 * fixed_div: Divide two fixed-point numbers using 486 assembly
 *
 * Parameters:
 *   a - Dividend (fixed-point value)
 *   b - Divisor (fixed-point value)
 *
 * Returns:
 *   Result of a / b
 *   Returns FIXED_DIV_ZERO if b is zero
 *
 * Notes:
 *   - Uses IDIV instruction with pre-scaling
 *   - Pre-shifts dividend by 16 to maintain precision
 *   - May overflow if result exceeds 32767.99998474121094
 *   - May underflow if result is less than -32768.0
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
 *
 * Notes:
 *   - Uses conditional jump-free 486 assembly for efficiency
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
