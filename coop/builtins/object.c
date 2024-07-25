//
// Created by t-danachum on 22/05/2024.
//


#include <string.h>
#include <stdarg.h>
#include "object.h"
#include "../memory/allocator.h"
#include "macros.h"
#include "functions/attr/getattr.h"

#include "types/__init__.h"


#define init_object(type_) (Object){ \
    .type=type_,                     \
    .num_attributes=0,               \
    .attributes=NULL,                \
    .data=NULL                       \
}

Object *_new_object_impl(Object *type) {
    Object * res = acquire(sizeof(Object));
    if (res != NULL)
        *res = init_object(type);
    return res;
}

bool object_equals(const Object *a, const Object *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (not(a->type == b->type)) return false;
    if (a->type == Type) return object_equals(getattr(a, "__name__"), getattr(b, "__name__"));
    if (a->type == String) return explicitgetfunc(String, __eq__)(a, b);
    if (a->type == Integer) return explicitgetfunc(Integer, __eq__)(a, b);
    if (a->type == Number) return number_equals(a, b);
    if (a->type == Boolean) return explicitgetfunc(Boolean, __eq__)(a, b);
    if (a->type == Array) return explicitgetfunc(Array, __eq__)(a, b);
    if (a->type == Union) return union_equals(a, b);
    if (a->type == Function) return explicitgetfunc(Function, __eq__)(a, b);
    return a == b;
}

Attribute *new_attr(const char *key, Object *value) {
    char *dup_key = acquire(sizeof(char) * (strlen(key) + 1));
    if (dup_key == NULL) return NULL;
    strcpy(dup_key, key);
    Attribute *res = acquire(sizeof(Attribute));
    if (res == NULL) {
        release(dup_key);
        return NULL;
    }
    *res = (Attribute) {dup_key, value};
    return res;
}