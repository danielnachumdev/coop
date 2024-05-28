//
// Created by danie on 28/05/2024.
//
#include <string.h>
#include "../coop/globals.h"
#include "../coop/builtins/__init__.h"
#include "../coop/testing/test.h"

int num_tests = 0;
int passed_tests = 0;


void _main(void) {
    Object *a = getattr(__global__field__name__field__name__, NAME);
    ASSERT_NOT_NULL(a);
    Object *b = new_string(NAME);
    ASSERT_NOT_NULL(b);
    ASSERT_OBJECT_EQUALS(a, b);
    ASSERT_OBJECT_EQUALS(getattr(__global__field__name__field__name__, LEN), new_integer(strlen(NAME)));

    Object *c = getattr(__global__field__len__field__name__, NAME);
    ASSERT_NOT_NULL(c);
    Object *d = new_string(LEN);
    ASSERT_NOT_NULL(d);
    ASSERT_OBJECT_EQUALS(c, d);
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