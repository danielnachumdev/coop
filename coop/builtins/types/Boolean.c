//
// Created by danie on 28/05/2024.
//

#include "Boolean.h"

Object *Boolean = NULL;

void __init_boolean(void) {
    Boolean = new_object(Type);
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
