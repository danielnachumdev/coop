//
// Created by t-danachum on 21/05/2024.
//

#include "_main.h"
#include "coop/memory/allocator.h"
#include "coop/object.h"
#include "coop/macros.h"
#include "coop/builtins/functions/print.h"
#include "coop/builtins/functions/getattr.h"

void _main(void) {
    Object *function_new_string = getattr(String, "__init__");
    println(function_new_string);
    Object *(*new_string)(const char *) = cast(function_new_string->data, Object * (*)(const char *));
    Object *daniel = new_string("daniel");
    println(daniel);
}