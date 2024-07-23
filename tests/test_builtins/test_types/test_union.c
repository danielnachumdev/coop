//
// Created by danie on 21/07/2024.
//

#include "test_union.h"
#include "../../__framework__.h"

void test_union(void) {
    Object *u1 = new_union(2, Integer, Function);
    Object *u2 = new_union(2, Function, Integer);
    ASSERT_OBJECT_EQUALS(u1, u2);
    ASSERT_TRUE(isinstance(u1, u2));
    ASSERT_TRUE(isinstance(u2, u1));
}