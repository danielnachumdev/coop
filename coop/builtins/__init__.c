//
// Created by t-danachum on 27/05/2024.
//

#include "__init__.h"

void init_types(void) {
    //    THE ORDER MATTERS!
    __init_type();
    __init_number();
    __init_string();
    __init_integer();
    __init_function();
    __init_array();
    __init_boolean();
    __init_union();
}

void init_builtins(void) {
    init_types();
    setattr(Type, NAME, new_string("Type"));
    setattr(String, NAME, new_string("String"));
    setattr(Number, NAME, new_string("Number"));
    setattr(Integer, NAME, new_string("Integer"));
    setattr(Function, NAME, new_string("Function"));
    setattr(Array, NAME, new_string("Array"));
    setattr(Boolean, NAME, new_string("Boolean"));
    setattr(Union, NAME, new_string("Union"));
}