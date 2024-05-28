//
// Created by t-danachum on 27/05/2024.
//

#include <string.h>
#include "__init__.h"
#include "../globals.h"

Object *__global__field__name__field__name__ = NULL;
Object *__global__field__len__field__name__ = NULL;

void init_builtins(void) {
//    THE ORDER MATTERS!
    __init_type();
    __init_number();
    __init_string();
    __init_integer();
    __init_function();
    __init_field();
    __init_array();
    __init_boolean();

//  diagrams/flow1.png
    Object *string__len__ = new_string_explicit(LEN, NULL);
    Object *string__len__value__len__ = new_integer(strlen(LEN));
    Object *string__name__ = new_string_explicit(NAME, NULL);
    Object *string__name__value__len__ = new_integer(strlen(NAME));

    Object *string__name__field__len__ = new_field_explicit(NULL, string__name__value__len__);
    Object *string__len__field__len__ = new_field_explicit(NULL, string__len__value__len__);
    __global__field__len__field__name__ = new_field_explicit(NULL, string__len__);
    __global__field__name__field__name__ = new_field_explicit(NULL, string__name__);

    append_attr(string__name__field__len__, __global__field__len__field__name__);
    append_attr(string__len__field__len__, __global__field__len__field__name__);
    append_attr(__global__field__len__field__name__, __global__field__name__field__name__);
    append_attr(__global__field__name__field__name__, __global__field__name__field__name__);
//    end diagrams/flow1.png

    append_attr(Type, new__name__field("Type"));
    append_attr(String, new__name__field("String"));
    append_attr(Integer, new__name__field("Integer"));
    append_attr(Number, new__name__field("Number"));
    append_attr(Boolean, new__name__field("Boolean"));
    append_attr(Array, new__name__field("Array"));
}