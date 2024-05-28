//
// Created by t-danachum on 27/05/2024.
//

#include <string.h>
#include "Function.h"
#include "../../globals.h"

Object *Function = NULL;

void init_function(void) {
    Function = acquire(sizeof(Object));
    *Function = init_object(Type);
}

Object *new_function(const char *name, void *(*impl)()) {
    if (name == NULL || impl == NULL) return NULL;
    Object *res = new_object(Function);
    if (res == NULL) return NULL;

//    new_field()




    res->data = impl;
    return res;
}