//
// Created by danie on 21/07/2024.
//

#include "test_setattr.h"
#include "../../../__framework__.h"

void test_setattr(void) {
    Object *obj = new_object(Type);
    char *key = "daniel";
    Object *v1 = new_integer(1);
    Object *v2 = new_integer(2);
    setattr(obj, key, v1);
    ASSERT_OBJECT_EQUALS(getattr(obj, key)->data, v1);
    setattr(obj, key, v2);
    ASSERT_OBJECT_EQUALS(getattr(obj, key)->data, v2);
}