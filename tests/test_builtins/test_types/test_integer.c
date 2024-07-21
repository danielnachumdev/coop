//
// Created by danie on 21/07/2024.
//

#include "test_integer.h"
#include "../../../coop/__init__.h"

void test_integer(void) {
    assert_true(isinstance(new_integer(1), Integer));
    assert_true(isinstance(new_integer(1), Number));
    assert_true(isinstance(new_integer(1), Type));
    assert_objects_equal(new_integer(1), new_integer(1));
    assert_objects_equal(new_integer(0), new_integer(0));
    assert_objects_equal(new_integer(-1), new_integer(-1));
}