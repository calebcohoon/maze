/*
 * tmath.c
 *
 * Implementation of the math testing framework
 */

#include "tmath.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

const char *output_sep = "------------------------------\n";

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
    results->current_suite = NULL;
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
    printf(output_sep);
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
    printf(output_sep);
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
void test_run(test_results_t *results, int (*test_func)(void), const char *test_name) {
    printf("Running test: %s...", test_name);

    results->tests_run++;

    if (test_func()) {
        results->tests_passed++;
        printf("PASSED\n");
    } else {
        results->tests_failed++;
    }
}

/*
 * test_fail: Record a test failure with a message
 *
 * Parameters:
 *  message - Description of why the test failed
 */
void test_fail(const char *message) {
    printf("FAILED\n");
    printf("  %s\n", message);
}

/*
 * test_fail_int: Record a test failure for integer comparison
 *
 * Parameters:
 *  expected - Expected integer value
 *  actual   - Actual integer value
 */
void test_fail_int(int expected, int actual) {
    printf("FAILED\n");
    printf("  Expected %d, got %d\n", expected, actual);
}

/*
 * test_fail_float: Record a test failure for floating point comparison
 *
 * Parameters:
 *  expected - Expected float value
 *  actual   - Actual float value
 */
void test_fail_float(float expected, float actual) {
    printf("FAILED\n");
    printf("  Expected %f, got %f\n", expected, actual);
}

/*
 * test_print_results: Print final test results
 *
 * Parameters:
 *  results - Pointer to test results structure to print
 */
void test_print_results(const test_results_t *results) {
    printf("\nFinal Results:\n");
    printf(output_sep);
    printf("Total tests: %d\n", results->tests_run);
}
