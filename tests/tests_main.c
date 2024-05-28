//
// Created by danie on 28/05/2024.
//
#include <string.h>
#include "../coop/globals.h"
#include "../coop/builtins/__init__.h"
#include "../coop/testing/test.h"

int num_tests = 0;
int passed_tests = 0;


void test_global_constants(void) {
    ASSERT_OBJECT_EQUALS(getattr(__global__field__name__field__name__, NAME), new_string(NAME));
    ASSERT_OBJECT_EQUALS(getattr(__global__field__name__field__name__, LEN), new_integer(strlen(NAME)));
    ASSERT_OBJECT_EQUALS(getattr(__global__field__len__field__name__, NAME), new_string(LEN));
}

void test_isinstance(void) {
    ASSERT_TRUE(isinstance(Integer, Number));
    ASSERT_TRUE(isinstance(Number, Type));
    ASSERT_TRUE(isinstance(Integer, Type));
    Object *Attr = new_union(2, Field, Function);
    ASSERT_TRUE(isinstance(Field, Attr));
    ASSERT_TRUE(isinstance(Function, Attr));
    ASSERT_TRUE(isinstance(__global__field__name__field__name__, Field));
    ASSERT_TRUE(isinstance(__global__field__name__field__name__, Attr));
}

void _main(void) {
    test_global_constants();
    test_isinstance();
}

int main(void) {
    init_builtins();
    println(new_string("====================================================="));
    println(new_string("Testing started."));
    println(new_string("====================================================="));
    println();
    _main();
    println();
    println(new_string("====================================================="));
    println(new_string("Testing finished successfully."));
    println(new_string("====================================================="));
    println(new_string("Passed "), new_integer(passed_tests), new_string("/"), new_integer(num_tests));
    get_allocator()->clear();
    return 0;
}