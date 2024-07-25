//
// Created by danie on 21/07/2024.
//

#include "test_setattr.h"
#include "../../../__framework__.h"

void test_setattr(void) {
    Integer__init___prototype nint = Integer__init__;
    Object *obj = new_object(Type);
    char *key = "daniel";
    Object *v1 = nint(1);
    Object *v2 = nint(2);
    setattr(obj, key, v1);
    ASSERT_OBJECT_EQUALS(getattr(obj, key), v1);
    setattr(obj, key, v2);
    ASSERT_OBJECT_EQUALS(getattr(obj, key), v2);
}