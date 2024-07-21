//
// Created by danie on 21/07/2024.
//
#include <stdbool.h>
#include "test.h"
#include "../builtins/macros.h"
#include "../builtins/types/__init__.h"
#include "../builtins/functions/print.h"

extern int num_tests;
extern int passed_tests;

bool assert_objects_equal(const Object *obj1, const Object *obj2) {
    bool res = object_equals(obj1, obj2);
    passed_tests += res;
    if (not(res))
        println(
                new_string(__FILE__ " at function"),
                new_string(__func__),
                new_string("at line"),
                new_integer(__LINE__),
                new_string("| FAILED\n"),
                new_string("\tGot     :"),
                obj1,
                new_string("=="),
                obj2,
                new_string("  => FALSE\n")
        );
    num_tests += 1;
    return res;
}

bool assert_objects_not_equal(const Object *obj1, const Object *obj2) {
    bool res = not(object_equals(obj1, obj2));
    passed_tests += res;
    if (not(res))
        println(
                new_string(__FILE__ " at function"),
                new_string(__func__),
                new_string("at line"),
                new_integer(__LINE__),
                new_string("| FAILED\n"),
                new_string("\tGot     :"),
                obj1,
                new_string("=="),
                obj2,
                new_string("  => FALSE\n")
        );
    num_tests += 1;
    return res;
}

bool assert_true(bool x) {
    return assert_objects_equal(new_boolean(x), new_boolean(true));
}

bool assert_false(bool x) {
    return assert_true(not(x));
}

bool assert_null(const Object *obj) {
    return assert_true(obj == NULL);
}

bool assert_not_null(const Object *obj) {
    return assert_true(obj != NULL);
}

void test_start(const char *segment_name) {
    if (segment_name == NULL) return;
    printf("============== TEST '%s' STARTED ==============\n", segment_name);
}

void test_end(const char *segment_name) {
    if (segment_name == NULL) return;
    printf("============== TEST '%s' FINISHED ==============\n", segment_name);
}