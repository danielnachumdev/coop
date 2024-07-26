//
// Created by danie on 21/07/2024.
//

#include "test_isinstance.h"
#include "../../__framework__.h"

void test_isinstance(void) {
    Integer__init___prototype nint = Integer__init__;
    ASSERT_TRUE(isinstance(Integer, Number));
    ASSERT_TRUE(isinstance(Number, Type));
    ASSERT_TRUE(isinstance(Integer, Type));
    Object *union_ = implicitgetfunc(Union, __init__)(2, Integer, Function);
    ASSERT_TRUE(isinstance(Integer, union_));
    ASSERT_TRUE(isinstance(Function, union_));
    ASSERT_TRUE(isinstance(__new_string(""), String));
    ASSERT_TRUE(isinstance(nint(1), Integer));
    ASSERT_FALSE(isinstance(nint(1), String));
}