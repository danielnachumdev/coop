//
// Created by danie on 21/07/2024.
//

#include "test_integer.h"
#include "../../__framework__.h"

void test_integer(void) {
    Integer__init___prototype nint = Integer__init__;
    ASSERT_TRUE(isinstance(nint(1), Integer));
    ASSERT_TRUE(isinstance(nint(1), Number));
    ASSERT_TRUE(isinstance(nint(1), Type));
    ASSERT_OBJECT_EQUALS(nint(1), nint(1));
    ASSERT_OBJECT_EQUALS(nint(0), nint(0));
    ASSERT_OBJECT_EQUALS(nint(-1), nint(-1));
}