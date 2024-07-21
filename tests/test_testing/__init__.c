//
// Created by danie on 21/07/2024.
//

#include "__init__.h"
#include "../../coop/__init__.h"

void test_testing(void) {
    assert_objects_equal(new_boolean(true), new_boolean(true));
    assert_objects_equal(new_boolean(false), new_boolean(false));
    assert_objects_not_equal(new_boolean(true), new_boolean(false));
    assert_not_null(new_boolean(true));
    assert_null(NULL);
    assert_objects_equal(new_string("Daniel"), new_string("Daniel"));
    assert_objects_not_equal(new_string("Danielle"), new_string("Daniel"));
    assert_objects_not_equal(new_string("Daniel"), new_string("Danielle"));
}