//
// Created by danie on 21/07/2024.
//

#include "__init__.h"
#include "../__framework__.h"

void test_testing(void) {
    Boolean__init___prototype nbool = Boolean__init__;
    ASSERT_OBJECT_EQUALS(nbool(true), nbool(true));
    ASSERT_OBJECT_EQUALS(nbool(false), nbool(false));
    ASSERT_OBJECT_NOT_EQUALS(nbool(true), nbool(false));
    ASSERT_NOT_NULL(nbool(true));
    ASSERT_NULL(NULL);
    ASSERT_OBJECT_EQUALS(__new_string("Daniel"), __new_string("Daniel"));
    ASSERT_OBJECT_NOT_EQUALS(__new_string("Danielle"), __new_string("Daniel"));
    ASSERT_OBJECT_NOT_EQUALS(__new_string("Daniel"), __new_string("Danielle"));
}