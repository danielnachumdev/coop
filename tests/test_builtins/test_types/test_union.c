//
// Created by danie on 21/07/2024.
//

#include "test_union.h"
#include "../../../coop/__init__.h"

void test_union(void) {
    assert_objects_equal(new_union(2, Field, Function), new_union(2, Function, Field));
}