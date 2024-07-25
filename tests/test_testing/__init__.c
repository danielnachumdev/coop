//
// Created by danie on 21/07/2024.
//

#include "__init__.h"
#include "../__framework__.h"

void test_testing(void) {
    ASSERT_OBJECT_EQUALS(new_boolean(true), new_boolean(true));
    ASSERT_OBJECT_EQUALS(new_boolean(false), new_boolean(false));
    ASSERT_OBJECT_NOT_EQUALS(new_boolean(true), new_boolean(false));
    ASSERT_NOT_NULL(new_boolean(true));
    ASSERT_NULL(NULL);
    ASSERT_OBJECT_EQUALS(__new_string("Daniel"), __new_string("Daniel"));
    ASSERT_OBJECT_NOT_EQUALS(__new_string("Danielle"), __new_string("Daniel"));
    ASSERT_OBJECT_NOT_EQUALS(__new_string("Daniel"), __new_string("Danielle"));
}