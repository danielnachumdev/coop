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
    if (a->type == String) return strcmp(a->data, b->data) == 0;
    if (a->type == Integer) return *cast(a->data, unsigned int *) == *cast(b->data, unsigned int *);
    if (a->type == Boolean) return *cast(a->data, bool *) == *cast(b->data, bool *);
    if (a->type == Array) {
        Object *len;
        if (not(object_equals(len = getattr(a, LEN), getattr(b, LEN)))) return false;
        for (unsigned int i = 0; i < *cast(len->data, unsigned int *); ++i)
            if (not(object_equals(array_get(a, i), array_get(b, i)))) return false;
    }
    if (a->type == Union) return object_equals(a->data, b->data);
    return a == b;
}