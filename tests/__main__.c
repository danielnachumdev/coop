//
// Created by danie on 28/05/2024.
//
#include <string.h>
#include <stdio.h>
#include "__init__.h"
#include "../coop/testing/__init__.h"
#include "../coop/__init__.h"

int num_tests = 0;
int passed_tests = 0;

//
//void test_global_constants(void) {
//    getattr(__global__field__name__field__name__, LEN);
//    ASSERT_OBJECT_EQUALS(getattr(__global__field__name__field__name__, NAME), new_string(NAME));
//    ASSERT_OBJECT_EQUALS(getattr(__global__field__name__field__name__, LEN), new_integer(strlen(NAME)));
//    ASSERT_OBJECT_EQUALS(getattr(__global__field__len__field__name__, NAME), new_string(LEN));
//}


int main(void) {
    test_start("BACKEND");
    test_backend();
    test_end("BACKEND");
    init_coop();
    test_start("TESTING");
    test_testing();
    test_end("TESTING");
    test_start("BUILTINS");
    test_builtins();
    test_end("BUILTINS");
    shutdown();
    printf("============= %d / %d tests have passed =============\n", passed_tests, num_tests);
    return 0;
}