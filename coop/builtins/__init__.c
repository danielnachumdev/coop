//
// Created by t-danachum on 27/05/2024.
//

#include <string.h>
#include "__init__.h"

Object *__global__field__name__field__name__ = NULL;
Object *__global__field__len__field__name__ = NULL;

void init_types(void) {
    //    THE ORDER MATTERS!
    __init_type();
    __init_number();
    __init_string();
    __init_integer();
    __init_function();
    __init_field();
    __init_array();
    __init_boolean();
    __init_union();
}

void flow1(void) {
    //  diagrams/flow1.png
    Object *string__len__ = new_string_explicit(LEN, NULL);
    Object *string__len__value__len__ = new_integer(strlen(LEN));
    Object *string__name__ = new_string_explicit(NAME, NULL);
    Object *string__name__value__len__ = new_integer(strlen(NAME));

    Object *string__name__field__len__ = new_field_explicit(NULL, string__name__value__len__);
    Object *string__len__field__len__ = new_field_explicit(NULL, string__len__value__len__);
    __global__field__len__field__name__ = new_field_explicit(NULL, string__len__);
    __global__field__name__field__name__ = new_field_explicit(NULL, string__name__);

    __append_attr(string__name__field__len__, __global__field__len__field__name__);
    __append_attr(string__len__field__len__, __global__field__len__field__name__);
    __append_attr(__global__field__len__field__name__, __global__field__name__field__name__);
    __append_attr(__global__field__name__field__name__, __global__field__name__field__name__);
//    end diagrams/flow1.png
}

void init_builtins(void) {
    init_types();
    flow1();
    __append_attr(Type, new__name__field("Type"));
    __append_attr(String, new__name__field("String"));
    __append_attr(Number, new__name__field("Number"));
    __append_attr(Integer, new__name__field("Integer"));
    __append_attr(Function, new__name__field("Function"));
    __append_attr(Field, new__name__field("Field"));
    __append_attr(Array, new__name__field("Array"));
    __append_attr(Boolean, new__name__field("Boolean"));
    __append_attr(Union, new__name__field("Union"));
}