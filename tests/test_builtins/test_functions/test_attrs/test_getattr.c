//
// Created by danie on 21/07/2024.
//

#include "test_getattr.h"
#include "../../../__framework__.h"

#define MISSING "asfjhbaslkjgfbalskbgag"
#define REPLACE "hashdjbasjhdjbasd"

void test_getattr(void) {
    ASSERT_NULL(getattr(__global__name__attr__->value, MISSING));
    ASSERT_NULL(getattr(__global__name__attr__->value, MISSING, NULL));
    ASSERT_NOT_NULL(getattr(__global__name__attr__->value, MISSING, new_boolean(true)));
    ASSERT_OBJECT_EQUALS(getattr(__global__name__attr__->value, MISSING, new_string(REPLACE)), new_string(REPLACE));
    ASSERT_TRUE(hasattr(__global__name__attr__->value, NAME));
    ASSERT_TRUE(hasattr(__global__name__attr__->value, LEN));
    ASSERT_TRUE(hasattr(__global__len__attr__->value, NAME));
    ASSERT_TRUE(hasattr(__global__len__attr__->value, LEN));
    ASSERT_OBJECT_EQUALS(getattr(__global__name__attr__->value, NAME), __global__name__attr__->value);
    ASSERT_OBJECT_EQUALS(getattr(__global__len__attr__->value, NAME), __global__name__attr__->value);
    ASSERT_OBJECT_EQUALS(getattr(__global__name__attr__->value, NAME), getattr(__global__len__attr__->value, NAME));
    ASSERT_OBJECT_NOT_EQUALS(getattr(__global__name__attr__->value, LEN), getattr(__global__len__attr__->value, LEN));
    ASSERT_OBJECT_EQUALS(getattr(getattr(__global__name__attr__->value, NAME), NAME), __global__len__attr__->value);
    ASSERT_OBJECT_EQUALS(getattr(getattr(__global__len__attr__->value, NAME), NAME), __global__len__attr__->value);
}