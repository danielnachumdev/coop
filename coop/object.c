//
// Created by t-danachum on 22/05/2024.
//


#include <string.h>
#include "object.h"
#include "globals.h"


#define init_object(type_) (Object){ \
    .type=type_,                     \
    .num_attributes=0,               \
    .attributes=NULL,                \
    .data=NULL                       \
}

Object *new_object(Object *type) {
    Object *res = acquire(sizeof(Object));
    if (res != NULL)
        *res = init_object(type);
    return res;
}

bool object_equals(const Object *a, const Object *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (not(a->type == b->type)) return false;
    if (a->type == Type) return object_equals(getattr(a, NAME), getattr(b, NAME));
    if (a->type == String) return string_equals(a, b);
    if (a->type == Integer) return integer_equals(a, b);
    if (a->type == Boolean) return boolean_equals(a, b);
    if (a->type == Array) return array_equals(a, b);
    if (a->type == Union) return union_equals(a, b);
    return a == b;
}