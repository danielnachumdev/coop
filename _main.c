//
// Created by t-danachum on 21/05/2024.
//

#include "_main.h"
#include "coop/__init__.h"

int num_tests = 0;
int passed_tests = 0;

void _main(void) {
    Object *function_new_string = new_function(
            "__init__",
            cast(new_string_explicit, void*(*)()),
            String,
            new_array(1, String)
    );
    dir(function_new_string);
////    append_attr(
////            function_new_string,
////            new_field_explicit(new_string(CALL),)
////    );
//    append_attr(String, function_new_string);
////    bool status = getattr(String, "__init__")->data == new_string_explicit;
////    println(new_string(status ? "True" : "False"));
}