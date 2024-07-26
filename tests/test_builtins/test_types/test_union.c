//
// Created by danie on 21/07/2024.
//

#include "test_union.h"
#include "../../__framework__.h"

void test_union(void) {
    Object *u1 = implicitgetfunc(Union, __init__)(2, Integer, Function);
    Object *u2 = implicitgetfunc(Union, __init__)(2, Function, Integer);
    ASSERT_OBJECT_EQUALS(u1, u2);
    ASSERT_TRUE(isinstance(Integer, u1));
    ASSERT_TRUE(isinstance(Integer, u2));
    ASSERT_TRUE(isinstance(Function, u1));
    ASSERT_TRUE(isinstance(Function, u2));
    ASSERT_FALSE(isinstance(String, u1));
    ASSERT_FALSE(isinstance(String, u2));
}