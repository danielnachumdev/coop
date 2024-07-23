//
// Created by danie on 28/05/2024.
//

#include "Boolean.h"
#include "../../memory/allocator.h"
#include "../macros.h"
#include "String.h"
#include "../functions/attr/setattr.h"

Object *Boolean = NULL;

void __init_boolean(void) {
    Boolean = new_object(Type);
    setattr(Boolean, "__name__", new_string("Boolean"));
}

Object *new_boolean(bool v) {
    Object *res = new_object(Boolean);
    if (res == NULL) return NULL;
    res->data = acquire(sizeof(bool));
    if (res->data == NULL) {
        release(res);
        return NULL;
    }
    *cast(res->data, bool *) = v;
    return res;
}

bool boolean_equals(const Object *a, const Object *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (not(a->type == b->type)) return false;
    if (not(a->type == Boolean)) return false;
    return *cast(a->data, bool *) == *cast(b->data, bool *);
}

void boolean_print(const Object *obj) {
    printf("%s", *cast(obj->data, bool *) ? "true" : "false");
}