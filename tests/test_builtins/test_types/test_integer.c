//
// Created by danie on 21/07/2024.
//

#include "test_integer.h"
#include "../../__framework__.h"

void test_integer(void) {
    ASSERT_TRUE(isinstance(new_integer(1), Integer));
    ASSERT_TRUE(isinstance(new_integer(1), Number));
    ASSERT_TRUE(isinstance(new_integer(1), Type));
    ASSERT_OBJECT_EQUALS(new_integer(1), new_integer(1));
    ASSERT_OBJECT_EQUALS(new_integer(0), new_integer(0));
    ASSERT_OBJECT_EQUALS(new_integer(-1), new_integer(-1));
}