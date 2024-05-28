//
// Created by t-danachum on 27/05/2024.
//

#include "Integer.h"
#include "../../memory/allocator.h"

Object *Integer = NULL;

void init_integer(void) {
    Integer = acquire(sizeof(Object));
    *Integer = init_object(Number);
}


Object *new_integer(int n) {
    Object *res = new_object(Integer);
    res->data = acquire(sizeof(int));
    *((int *) res->data) = n;
    return res;
}