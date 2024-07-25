//
// Created by t-danachum on 27/05/2024.
//

#include "__init__.h"
#include "types/Node.h"

void init_builtins(void) {
    //    THE ORDER MATTERS!
    __init_type();
    __init_number();
    __init_integer();
    __init_string();
    setattr(Type, "__name__", __new_string("Type"));
    setattr(Integer, "__name__", __new_string("Integer"));
    __init_function();
    __init_type_functions();
    __init_string_functions();
    __init_integer_functions();
//    __init_number_functions();

    __init_array();
    __init_boolean();
    __init_union();
    __init_node();
    __init_list();
}