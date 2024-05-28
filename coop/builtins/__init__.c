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

//  diagrams/flow1.png
    Object *string__len__ = new_string_explicit(LEN, NULL);
    Object *string__len__value__len__ = new_integer(strlen(LEN));
    Object *string__name__ = new_string_explicit(NAME, NULL);
    Object *string__name__value__len__ = new_integer(strlen(NAME));

    Object *string__name__field__len__ = new_field_explicit(NULL, string__name__value__len__);
    Object *string__len__field__len__ = new_field_explicit(NULL, string__len__value__len__);
    __global__field__len__field__name__ = new_field_explicit(NULL, string__len__);
    __global__field__name__field__name__ = new_field_explicit(NULL, string__name__);

    append_field(string__name__field__len__, __global__field__len__field__name__);
    append_field(string__len__field__len__, __global__field__len__field__name__);
    append_field(__global__field__len__field__name__, __global__field__name__field__name__);
    append_field(__global__field__name__field__name__, __global__field__name__field__name__);

    println(string__len__);
    println(string__len__value__len__);
    println(string__name__);
    println(string__name__value__len__);

    println(string__name__field__len__);
    println(string__len__field__len__);
    println(__global__field__len__field__name__);
    println(__global__field__name__field__name__);
}