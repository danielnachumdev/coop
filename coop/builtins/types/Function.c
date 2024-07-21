//
// Created by t-danachum on 27/05/2024.
//

#include "Function.h"
#include "__init__.h"
#include "../constants.h"
#include "../macros.h"
#include "../functions/attr/setattr.h"

Object *Function = NULL;

void __init_function(void) {
    Function = new_object(Type);
}

bool function_equals(const Object *a, const Object *b) {
    return false;
}

Object *new_function(const char *name, void *(*impl)(), Object *return_type, Object *arguments_array) {
    if (name == NULL || impl == NULL) return NULL;
    Object *res = new_object(Function);
    if (res == NULL) return NULL;

//    diagrams/flow2.png
    __append_attr(res, new__name__field(name));
    __append_attr(res, new_field(RETURN_TYPE, return_type));
    __append_attr(res, new_field(ARGS, arguments_array));

    res->data = impl;
    return res;
}

Object *new_runnable(const char *name, void (*impl)(void)) {
    return new_function(name, cast(impl, void *(*)()), NULL, NULL);
}