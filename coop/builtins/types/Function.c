//
// Created by t-danachum on 27/05/2024.
//

#include "Function.h"
#include "../../globals.h"

Object *Function = NULL;

void __init_function(void) {
    Function = new_object(Type);
}

Object *new_function(const char *name, void *(*impl)()) {
    if (name == NULL || impl == NULL) return NULL;
    Object *res = new_object(Function);
    if (res == NULL) return NULL;

//    diagrams/flow2.png

    Object *name_field = new__name__field(name);
    append_field(res, name_field);


    res->data = impl;
    return res;
}