//
// Created by danie on 21/07/2024.
//

#include "test_union.h"
#include "../../__framework__.h"

void test_union(void) {
    ASSERT_OBJECT_EQUALS(new_union(2, Field, Function), new_union(2, Function, Field));
}