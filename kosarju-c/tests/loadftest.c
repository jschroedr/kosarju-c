/*
 * File:   loadftest.c
 * Author: jake
 *
 * Created on Nov 15, 2020, 6:57:09 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "../loadf.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

char * getExampleFileName() {
   return "./test-files/input_mostlyCycles_1_8.txt";
}


void testLoadFile() {
    char * fname = getExampleFileName();
    FILE * f = loadFile(fname);
    CU_ASSERT_PTR_NOT_NULL(f);
}


void testLoadFromAdjacencyList() {
    char * fname = getExampleFileName();
    int * nrows;
    char ** rows = loadFromAdjacencyList(fname, nrows);
    CU_ASSERT(*nrows > 0);
    CU_ASSERT_PTR_NOT_NULL(rows);
    char * row = rows[0];
    int rlen = strlen(row);
    if (rlen > 0) {
        CU_PASS("first row of rows had characters");
    } else {
        CU_FAIL("first row of rows had no characters");
    }
}

int setup_suite(void) { return 0; }
int teardown_suite(void) { return 0; }


int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("loadftest", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if (
            (NULL == CU_add_test(pSuite, "testLoadFile", testLoadFile)) ||
            (NULL == CU_add_test(pSuite, "testLoadFromAdjacencyList", testLoadFromAdjacencyList))
        ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    // CU_cleanup_registry();
    return CU_get_error();
}
