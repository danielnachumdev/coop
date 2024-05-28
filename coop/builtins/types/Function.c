//
// Created by t-danachum on 27/05/2024.
//

#include "Function.h"
#include "../../globals.h"

Object *Function = NULL;

void __init_function(void) {
    Function = new_object(Type);
}

Object *new_function(const char *name, void *(*impl)(), Object *return_type, Object *arguments_array) {
    if (name == NULL || impl == NULL) return NULL;
    Object *res = new_object(Function);
    if (res == NULL) return NULL;

//    diagrams/flow2.png
    append_attr(res, new__name__field(name));
    append_attr(res, new_field_explicit(new__name__field(RETURN_TYPE), return_type));
    append_attr(res, new_field_explicit(new__name__field(ARGS), arguments_array));

    res->data = impl;
    return res;
}

Object *new_runnable(const char *name, void (*impl)(void)) {
    return new_function(name, cast(impl, void *(*)()), NULL, NULL);
}