//
// Created by t-danachum on 27/05/2024.
//

#include "__init__.h"

void init_builtins(void) {
    //    THE ORDER MATTERS!
    __init_type();
    __init_string();
    setattr(Type, "__name__", __new_string("Type"));
    __init_function();
    __init_string_functions();

    __init_number();
    __init_integer();
    __init_array();
    __init_boolean();
    __init_union();
}