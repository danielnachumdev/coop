//
// Created by t-danachum on 27/05/2024.
//

#include "Integer.h"
#include "../../memory/allocator.h"

Object *Integer = NULL;

void __init_integer(void) {
    Integer = new_object(Number);
}


Object *new_integer(unsigned long n) {
    Object *res = new_object(Integer);
    if (res == NULL) return NULL;
    res->data = acquire(sizeof(unsigned long));
    if (res->data == NULL) {
        release(res);
        return NULL;
    }
    *((unsigned long *) res->data) = n;
    return res;
}