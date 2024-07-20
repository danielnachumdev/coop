//
// Created by danie on 28/05/2024.
//
#include <string.h>
#include "__init__.h"

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
    test_backend();
//    test_builtins();
    return 0;
}