//
// Created by danie on 21/07/2024.
//

#include "test_isinstance.h"
#include "../../__framework__.h"

void test_isinstance(void) {
    ASSERT_TRUE(isinstance(Integer, Number));
    ASSERT_TRUE(isinstance(Number, Type));
    ASSERT_TRUE(isinstance(Integer, Type));
    Object *Attr = new_union(2, Integer, Function);
    ASSERT_TRUE(isinstance(Integer, Attr));
    ASSERT_TRUE(isinstance(Function, Attr));
    ASSERT_TRUE(isinstance(new_string(""), String));
    ASSERT_TRUE(isinstance(new_integer(1), Integer));
    ASSERT_FALSE(isinstance(new_integer(1), String));
}