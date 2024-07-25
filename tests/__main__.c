//
// Created by danie on 28/05/2024.
//
#include <string.h>
#include <stdio.h>
#include "__init__.h"
#include "../coop/__init__.h"
#include "__framework__.h"

int num_tests = 0;
int passed_tests = 0;

//
//void test_global_constants(void) {
//    getattr(__global__name__attr__, LEN);
//    ASSERT_OBJECT_EQUALS(getattr(__global__name__attr__, NAME), __new_string(NAME));
//    ASSERT_OBJECT_EQUALS(getattr(__global__name__attr__, LEN), new_integer(strlen(NAME)));
//    ASSERT_OBJECT_EQUALS(getattr(__global__len__attr__, NAME), __new_string(LEN));
//}


int main(void) {
    TEST_START("BACKEND");
    test_backend();
    TEST_END("BACKEND");
    coop_setup();
    TEST_START("TESTING");
    test_testing();
    TEST_END("TESTING");
    TEST_START("BUILTINS");
    test_builtins();
    TEST_END("BUILTINS");
    coop_teardown();
    printf("============= %d / %d tests have passed =============\n", passed_tests, num_tests);
    return 0;
}