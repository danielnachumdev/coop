//
// Created by t-danachum on 22/05/2024.
//


#include "object.h"
#include "memory/allocator.h"



Object *new_object(Object *type) {
    Object *res = acquire(sizeof(Object));
    if (res == NULL) return NULL;
    *res = init_object(type);
    return res;
}