//
// Created by danie on 28/05/2024.
//
#include <string.h>
#include "../coop/globals/__init__.h"
#include "../coop/builtins/__init__.h"
#include "../coop/testing/test.h"
#include "../coop/data_structures/hashset.h"
#include "../coop/__init__.h"
#include "data_structures/test_data_strucures.h"

int num_tests = 0;
int passed_tests = 0;


void test_global_constants(void) {
    ASSERT_OBJECT_EQUALS(getattr(__global__field__name__field__name__, NAME), new_string(NAME));
    ASSERT_OBJECT_EQUALS(getattr(__global__field__name__field__name__, LEN), new_integer(strlen(NAME)));
    ASSERT_OBJECT_EQUALS(getattr(__global__field__len__field__name__, NAME), new_string(LEN));
}

void test_integer(void) {
    ASSERT_TRUE(isinstance(new_integer(1), Integer));
    ASSERT_TRUE(isinstance(new_integer(1), Number));
    ASSERT_TRUE(isinstance(new_integer(1), Type));
    ASSERT_OBJECT_EQUALS(new_integer(1), new_integer(1));
    ASSERT_OBJECT_EQUALS(new_integer(0), new_integer(0));
    ASSERT_OBJECT_EQUALS(new_integer(-1), new_integer(-1));
}

void test_union(void) {
    ASSERT_OBJECT_EQUALS(new_union(2, Field, Function), new_union(2, Function, Field));
}

void test_primitives(void) {
    test_integer();
    test_union();
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
    ASSERT_TRUE(isinstance(new_string(""), String));
    ASSERT_TRUE(isinstance(new_integer(1), Integer));
    ASSERT_FALSE(isinstance(new_integer(1), String));
}

void _main(void) {
    test_global_constants();
    test_isinstance();
    test_primitives();
}


void test_coop(void) {
    init_coop();
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
    shutdown();
}

int main(void) {
    test_data_structures();
    test_coop();
    return 0;
}