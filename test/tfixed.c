/*
 * tfixed.c
 *
 * Test suite for fixed-point number system
 */

#include <stdio.h>

#include "..\include\fixed.h"
#include "tmath.h"

/* Test integer conversion */
int test_int_conversion(void) {
    int original = 42;
    fixed_t fixed = fixed_from_int(original);
    int result = fixed_to_int(fixed);

    TEST_ASSERT_EQUAL_INT(original, result);
}

/* Test zero conversion */
int test_zero(void) {
    fixed_t fixed = fixed_from_int(0);

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(fixed));
}

/* Test negative conversion */
int test_negative(void) {
    int original = -42;
    fixed_t fixed = fixed_from_int(original);
    int result = fixed_to_int(fixed);

    TEST_ASSERT_EQUAL_INT(original, result);
}

/* Test float conversion (approximate) */
int test_float_conversion(void) {
    float original = 3.14159f;
    fixed_t fixed = fixed_from_float(original);
    float result = fixed_to_float(fixed);

    TEST_ASSERT_EQUAL_FLOAT(original, result, 0.0001f);
}

/* Test float conversion with negative numbers */
int test_negative_float(void) {
    float original = -3.14159f;
    fixed_t fixed = fixed_from_float(original);
    float result = fixed_to_float(fixed);

    TEST_ASSERT_EQUAL_FLOAT(original, result, 0.0001f);
}

/* Test addition of positive numbers */
int test_addition_positive(void) {
    fixed_t a = fixed_from_int(5);
    fixed_t b = fixed_from_int(3);
    fixed_t result = fixed_add(a, b);

    TEST_ASSERT_EQUAL_INT(8, fixed_to_int(result));
}

/* Test addition with fractional components */
int test_addition_fractional(void) {
    fixed_t a = fixed_from_float(3.5f);
    fixed_t b = fixed_from_float(2.25f);
    fixed_t result = fixed_add(a, b);

    TEST_ASSERT_EQUAL_FLOAT(5.75f, fixed_to_float(result), 0.0001f);
}

/* Test subtraction of positive numbers */
int test_subtraction_positive(void) {
    fixed_t a = fixed_from_int(5);
    fixed_t b = fixed_from_int(3);
    fixed_t result = fixed_sub(a, b);

    TEST_ASSERT_EQUAL_INT(2, fixed_to_int(result));
}

/* Test subtraction with negative result */
int test_subtraction_negative_result(void) {
    fixed_t a = fixed_from_int(3);
    fixed_t b = fixed_from_int(5);
    fixed_t result = fixed_sub(a, b);

    TEST_ASSERT_EQUAL_INT(-2, fixed_to_int(result));
}

/* Test subtraction with fractional components */
int test_subtraction_fractional(void) {
    fixed_t a = fixed_from_float(5.5f);
    fixed_t b = fixed_from_float(2.25f);
    fixed_t result = fixed_sub(a, b);

    TEST_ASSERT_EQUAL_FLOAT(3.25f, fixed_to_float(result), 0.0001f);
}

/* Test multiplication of integers */
int test_multiplication_int(void) {
    fixed_t a = fixed_from_int(3);
    fixed_t b = fixed_from_int(4);
    fixed_t result = fixed_mul(a, b);

    TEST_ASSERT_EQUAL_INT(12, fixed_to_int(result));
}

/* Test multiplication of integers */
int test_multiplication_frac(void) {
    fixed_t a = fixed_from_float(2.5f);
    fixed_t b = fixed_from_float(1.5f);
    fixed_t result = fixed_mul(a, b);

    TEST_ASSERT_EQUAL_FLOAT(3.75f, fixed_to_float(result), 0.0001f);
}

/* Test multiplication by zero */
int test_multiplication_zero(void) {
    fixed_t a = fixed_from_int(123);
    fixed_t b = fixed_from_int(0);
    fixed_t result = fixed_mul(a, b);

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result));
}

/* Test multiplication with negative numbers */
int test_multiplication_negative(void) {
    fixed_t a = fixed_from_int(-3);
    fixed_t b = fixed_from_int(4);
    fixed_t result = fixed_mul(a, b);

    TEST_ASSERT_EQUAL_INT(-12, fixed_to_int(result));
}

/* Test multiplication with small fractions */
int test_multiplication_small_frac(void) {
    fixed_t a = fixed_from_float(0.1f);
    fixed_t b = fixed_from_float(0.2f);
    fixed_t result = fixed_mul(a, b);

    TEST_ASSERT_EQUAL_FLOAT(0.02f, fixed_to_float(result), 0.0001f);
}

/* Test basic division */
int test_division_basic(void) {
    fixed_t a = fixed_from_int(10);
    fixed_t b = fixed_from_int(2);
    fixed_t result = fixed_div(a, b);

    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result));
}

/* Test division with fractions */
int test_division_frac(void) {
    fixed_t a = fixed_from_float(5.0f);
    fixed_t b = fixed_from_float(2.0f);
    fixed_t result = fixed_div(a, b);

    TEST_ASSERT_EQUAL_FLOAT(2.5f, fixed_to_float(result), 0.0001f);
}

/* Test division by zero */
int test_division_by_zero(void) {
    fixed_t a = fixed_from_int(123);
    fixed_t b = fixed_from_int(0);
    fixed_t result = fixed_div(a, b);

    TEST_ASSERT("Division by zero returns error value", result == FIXED_DIV_ZERO);
}

/* Test division of zero */
int test_division_of_zero(void) {
    fixed_t a = fixed_from_int(0);
    fixed_t b = fixed_from_int(123);
    fixed_t result = fixed_div(a, b);

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result));
}

/* Test division with negative numbers */
int test_division_negative(void) {
    fixed_t a = fixed_from_int(-12);
    fixed_t b = fixed_from_int(4);
    fixed_t result = fixed_div(a, b);

    TEST_ASSERT_EQUAL_INT(-3, fixed_to_int(result));
}

/* Test division with small fractions */
int test_division_small_frac(void) {
    fixed_t a = fixed_from_float(0.02f);
    fixed_t b = fixed_from_float(0.1f);
    fixed_t result = fixed_div(a, b);

    TEST_ASSERT_EQUAL_FLOAT(0.2f, fixed_to_float(result), 0.0001f);
}

/* Test absolute value of a positive number */
int test_abs_positive(void) {
    fixed_t x = fixed_from_int(5);
    fixed_t result = fixed_abs(x);

    TEST_ASSERT_EQUAL_INT(5, fixed_to_int(result));
}

/* Test absolute value of a negative number */
int test_abs_negative(void) {
    fixed_t x = fixed_from_int(-3);
    fixed_t result = fixed_abs(x);

    TEST_ASSERT_EQUAL_INT(3, fixed_to_int(result));
}

/* Test absolute value of zero */
int test_abs_zero(void) {
    fixed_t x = fixed_from_int(0);
    fixed_t result = fixed_abs(x);

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result));
}

/* Test absolute value of a fraction */
int test_abs_fraction(void) {
    fixed_t x = fixed_from_float(-1.2f);
    fixed_t result = fixed_abs(x);

    TEST_ASSERT_EQUAL_FLOAT(1.2f, fixed_to_float(result), 0.0001f);
}

/* Test sign of positive number */
int test_sign_positive(void) {
    fixed_t x = fixed_from_int(42);

    TEST_ASSERT_EQUAL_INT(1, fixed_sign(x));
}

/* Test sign of negative number */
int test_sign_negative(void) {
    fixed_t x = fixed_from_int(-42);

    TEST_ASSERT_EQUAL_INT(-1, fixed_sign(x));
}

/* Test sign of zero */
int test_sign_zero(void) {
    fixed_t x = fixed_from_int(0);

    TEST_ASSERT_EQUAL_INT(0, fixed_sign(x));
}

/* Test sign of small positive fraction */
int test_sign_small_positive(void) {
    fixed_t x = fixed_from_float(0.0001f);

    TEST_ASSERT_EQUAL_INT(1, fixed_sign(x));
}

/* Test sign of small negative fraction */
int test_sign_small_negative(void) {
    fixed_t x = fixed_from_float(-0.0001f);

    TEST_ASSERT_EQUAL_INT(-1, fixed_sign(x));
}

/* Test negative detection of positive number */
int test_is_neg_positive(void) {
    fixed_t x = fixed_from_int(42);

    TEST_ASSERT_EQUAL_INT(0, fixed_is_neg(x));
}

/* Test negative detection of negative number */
int test_is_neg_negative(void) {
    fixed_t x = fixed_from_int(-42);

    TEST_ASSERT_EQUAL_INT(1, fixed_is_neg(x));
}

/* Test negative detection of zero */
int test_is_neg_zero(void) {
    fixed_t x = fixed_from_int(0);

    TEST_ASSERT_EQUAL_INT(0, fixed_is_neg(x));
}

/* Test negation of positive number */
int test_neg_positive(void) {
    fixed_t x = fixed_from_int(42);
    fixed_t result = fixed_neg(x);

    TEST_ASSERT_EQUAL_INT(-42, fixed_to_int(result));
}

/* Test negation of negative number */
int test_neg_negative(void) {
    fixed_t x = fixed_from_int(-42);
    fixed_t result = fixed_neg(x);

    TEST_ASSERT_EQUAL_INT(42, fixed_to_int(result));
}

/* Test negation of zero */
int test_neg_zero(void) {
    fixed_t x = fixed_from_int(0);
    fixed_t result = fixed_neg(x);

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result));
}

/* Test negation with fractions */
int test_neg_fraction(void) {
    fixed_t x = fixed_from_float(3.14159f);
    fixed_t result = fixed_neg(x);

    TEST_ASSERT_EQUAL_FLOAT(-3.14159f, fixed_to_float(result), 0.0001f);
}

/* Test negation with small fractions */
int test_neg_small_fraction(void) {
    fixed_t x = fixed_from_float(0.0001f);
    fixed_t result = fixed_neg(x);

    TEST_ASSERT_EQUAL_FLOAT(-0.0001f, fixed_to_float(result), 0.0001f);
}

/* Test square root of perfect square */
int test_sqrt_perfect(void) {
    fixed_t x = fixed_from_int(16);
    fixed_t result = fixed_sqrt(x);

    TEST_ASSERT_EQUAL_INT(4, fixed_to_int(result));
}

/* Test square root of zero */
int test_sqrt_zero(void) {
    fixed_t result = fixed_sqrt(FIXED_ZERO);

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result));
}

/* Test square root of one */
int test_sqrt_one(void) {
    fixed_t result = fixed_sqrt(FIXED_ONE);

    TEST_ASSERT_EQUAL_INT(1, fixed_to_int(result));
}

/* Test square root of non-perfect square */
int test_sqrt_non_perfect(void) {
    fixed_t x = fixed_from_int(2);
    fixed_t result = fixed_sqrt(x);

    TEST_ASSERT_EQUAL_FLOAT(1.4142f, fixed_to_float(result), 0.01f);
}

/* Test square root of negative */
int test_sqrt_negative(void) {
    fixed_t x = fixed_from_int(-16);
    fixed_t result = fixed_sqrt(x);

    TEST_ASSERT_EQUAL_INT(0, fixed_to_int(result));
}

int main(void) {
    test_results_t results;

    /* Initialize the test framework */
    test_init(&results);

    /* Run conversion tests */
    test_begin_suite(&results, "Fixed-Point Conversion");
    test_run(&results, test_int_conversion, "Integer Conversion");
    test_run(&results, test_zero, "Zero Conversion");
    test_run(&results, test_negative, "Negative Conversion");
    test_run(&results, test_float_conversion, "Float Conversion");
    test_run(&results, test_negative_float, "Negative Float");
    test_end_suite(&results);

    /* Run arithmetic tests */
    test_begin_suite(&results, "Fixed-Point Arithmetic");
    test_run(&results, test_addition_positive, "Addition of Positive Integers");
    test_run(&results, test_addition_fractional, "Addition with Fractions");
    test_run(&results, test_subtraction_positive, "Subtraction of Positive Integers");
    test_run(&results, test_subtraction_negative_result, "Subtraction with Negative Result");
    test_run(&results, test_subtraction_fractional, "Subtraction with Fractions");
    test_end_suite(&results);

    /* Run multiplication tests */
    test_begin_suite(&results, "Fixed-Point Multiplication");
    test_run(&results, test_multiplication_int, "Integer Multiplication");
    test_run(&results, test_multiplication_frac, "Fractional Multiplication");
    test_run(&results, test_multiplication_zero, "Multiplication by Zero");
    test_run(&results, test_multiplication_negative, "Negative Multiplication");
    test_run(&results, test_multiplication_small_frac, "Small Fraction Multiplication");
    test_end_suite(&results);

    /* Run division tests */
    test_begin_suite(&results, "Fixed-Point Division");
    test_run(&results, test_division_basic, "Basic Division");
    test_run(&results, test_division_frac, "Fractional Division");
    test_run(&results, test_division_by_zero, "Division by Zero");
    test_run(&results, test_division_of_zero, "Division of Zero");
    test_run(&results, test_division_negative, "Negative Division");
    test_run(&results, test_division_small_frac, "Small Fraction Division");
    test_end_suite(&results);

    /* Run absolute value tests */
    test_begin_suite(&results, "Fixed-Point Absolute Value");
    test_run(&results, test_abs_positive, "Absolute Value of Positive");
    test_run(&results, test_abs_negative, "Absolute value of Negative");
    test_run(&results, test_abs_zero, "Absolute Value of Zero");
    test_run(&results, test_abs_fraction, "Absolute Value of Fraction");
    test_end_suite(&results);

    /* Run sign tests */
    test_begin_suite(&results, "Fixed-Point Sign Function");
    test_run(&results, test_sign_positive, "Sign of Positive");
    test_run(&results, test_sign_negative, "Sign of Negative");
    test_run(&results, test_sign_zero, "Sign of Zero");
    test_run(&results, test_sign_small_positive, "Sign of Small Positive");
    test_run(&results, test_sign_small_negative, "Sign of Small Negative");
    test_end_suite(&results);

    /* Run is_negative tests */
    test_begin_suite(&results, "Fixed-Point Is Negative");
    test_run(&results, test_is_neg_positive, "Is Negative (Positive)");
    test_run(&results, test_is_neg_negative, "Is Negative (Negative)");
    test_run(&results, test_is_neg_zero, "Is Negative (Zero)");
    test_end_suite(&results);

    /* Run negation tests */
    test_begin_suite(&results, "Fixed-Point Negation");
    test_run(&results, test_neg_positive, "Negate Positive");
    test_run(&results, test_neg_negative, "Negate Negative");
    test_run(&results, test_neg_zero, "Negate Zero");
    test_run(&results, test_neg_fraction, "Negate Fraction");
    test_run(&results, test_neg_small_fraction, "Negate Small Fraction");
    test_end_suite(&results);

    /* Run square root tests */
    test_begin_suite(&results, "Fixed-Point Square Root");
    test_run(&results, test_sqrt_perfect, "Perfect Square Root");
    test_run(&results, test_sqrt_zero, "Square Root of Zero");
    test_run(&results, test_sqrt_one, "Square Root of One");
    test_run(&results, test_sqrt_non_perfect, "Non-Perfect Square Root");
    test_run(&results, test_sqrt_negative, "Negative Square Root");
    test_end_suite(&results);

    /* Print final results */
    test_print_results(&results);

    return 0;
}
