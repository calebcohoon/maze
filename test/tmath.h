/*
 * tmath.h
 *
 * Framework for testing mathematical operations with a focus on fixed-point
 * arithmetic, vector operations, and matrix transformations.
 */

#ifndef TMATH_H
#define TMATH_H

#include <math.h>

#include "..\include\defs.h"

typedef struct {
    int tests_run;
    int tests_passed;
    int tests_failed;
    char *current_suite;
} test_results_t;

/* Test assertion macros */
#define TEST_ASSERT(message, condition) \
    do {                                \
        if (!(condition)) {             \
            test_fail(message);         \
            return FALSE;               \
        }                               \
        return TRUE;                    \
    } while (0)

#define TEST_ASSERT_EQUAL_INT(expected, actual) \
    do {                                        \
        if ((expected) != (actual)) {           \
            test_fail_int(expected, actual);    \
            return FALSE;                       \
        }                                       \
        return TRUE;                            \
    } while (0)

#define TEST_ASSERT_EQUAL_FLOAT(expected, actual, epsilon) \
    do {                                                   \
        if (fabs((expected) - (actual)) > (epsilon)) {     \
            test_fail_float(expected, actual);             \
            return FALSE;                                  \
        }                                                  \
        return TRUE;                                       \
    } while (0)

/* Function prototypes */
void test_init(test_results_t *results);
void test_begin_suite(test_results_t *results, const char *suite_name);
void test_end_suite(test_results_t *results);
void test_run(test_results_t *results, int (*test_func)(void), const char *test_name);
void test_fail(const char *message);
void test_fail_int(int expected, int actual);
void test_fail_float(float expected, float actual);
void test_print_results(const test_results_t *results);

#endif /* TMATH_H */
