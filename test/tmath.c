/*
 * test_math.c
 *
 * Implementation of the math testing framework
 */

#include "tmath.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

/* File-scope variables for tracking current test state */
static char current_test_name[64];
static int current_test_failed;

/*
 * test_init: Initialize the test results structure
 *
 * Parameters:
 *  results - Pointer to test results structure to initialize
 */
void test_init(test_results_t *results) {
    results->tests_run = 0;
    results->tests_passed = 0;
    results->tests_failed = 0;
    results->current_suite = 0;
}

/*
 * test_begin_suite: Start a new test suite
 *
 * Parameters:
 *  results     - Pointer to test results structure
 *  suite_name  - Name of the test suite to begin
 */
void test_begin_suite(test_results_t *results, const char *suite_name) {
    printf("\nTest Suite: %s\n", suite_name);
    printf("----------\n");
    results->current_suite = (char *) suite_name;
    results->tests_passed = 0;
    results->tests_failed = 0;
}

/*
 * test_end_suite: End the current test suite
 *
 * Parameters:
 *  results - Pointer to test results structure
 */
void test_end_suite(test_results_t *results) {
    printf("----------\n");
    printf(
        "Suite complete: %d passed, %d failed\n\n", results->tests_passed, results->tests_failed);
}

/*
 * test_run: Execute a single test function
 *
 * Parameters:
 *  results     - Pointer to test results structure
 *  test_func   - Function pointer to the test to run
 *  test_name   - Name of the test being run
 */
void test_run(test_results_t *results, void (*test_func)(void), const char *test_name) {
    strncpy(current_test_name, test_name, sizeof(current_test_name) - 1);
    current_test_name[sizeof(current_test_name) - 1] = '\0';
    current_test_failed = 0;

    printf("Running test: %s...", test_name);
    test_func();

    results->tests_run++;

    if (!current_test_failed) {
        results->tests_passed++;
        printf("PASSED\n");
    } else {
        results->tests_failed++;
        printf("FAILED\n");
    }
}

/*
 * test_fail: Record a test failure with a message
 *
 * Parameters:
 *  message - Description of why the test failed
 */
void test_fail(const char *message) {
    if (!current_test_failed) {
        printf("FAILED\n");
        printf("  %s: %s\n", current_test_name, message);
        current_test_failed = 1;
    }
}

/*
 * test_fail_int: Record a test failure for integer comparison
 *
 * Parameters:
 *  expected - Expected integer value
 *  actual   - Actual integer value
 */
void test_fail_int(int expected, int actual) {
    if (!current_test_failed) {
        printf("FAILED\n");
        printf("  %s: Expected %d, got %d\n", current_test_name, expected, actual);
        current_test_failed = 1;
    }
}

/*
 * test_fail_float: Record a test failure for floating point comparison
 *
 * Parameters:
 *  expected - Expected float value
 *  actual   - Actual float value
 */
void test_fail_float(float expected, float actual) {
    if (!current_test_failed) {
        printf("FAILED\n");
        printf("  %s: Expected %f, got %f\n", current_test_name, expected, actual);
        current_test_failed = 1;
    }
}

/*
 * test_print_results: Print final test results
 *
 * Parameters:
 *  results - Pointer to test results structure to print
 */
void test_print_results(const test_results_t *results) {
    printf("\nFinal Results:\n");
    printf("----------\n");
    printf("Total tests: %d\n", results->tests_run);
}
