//
// Created by t-danachum on 21/05/2024.
//

#include "_main.h"
#include "coop/globals.h"


void _main(void) {
    Object *function_new_string = new_function("__init__", cast(new_string, void*(*)()));
    setattr(String, "__init__", function_new_string);
}