//
// Created by t-danachum on 21/05/2024.
//

#include "_main.h"
#include "coop/__init__.h"

void say_hi() {
    println(new_string("Hello, World!"));
    fflush(stdout);
}

void _main(void) {
    Object *daniel = new_object(Type);
    Object *say_hi_func = new_function("say_hi", cast(say_hi, void*(*)()), NULL, NULL);
    setattr(daniel, "__call__", say_hi_func);
    call(daniel);
    PASS;
}