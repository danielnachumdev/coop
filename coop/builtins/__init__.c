//
// Created by t-danachum on 27/05/2024.
//

#include <string.h>
#include "__init__.h"
#include "types/Integer.h"
#include "types/String.h"
#include "types/Type.h"
#include "types/Number.h"
#include "types/Function.h"
#include "types/Field.h"
#include "functions/print.h"

Object *__global__field__name__field__name__ = NULL;

void init_builtins(void) {
    init_type();
    init_number();
    init_string();
    init_integer();
    init_function();
    init_field();

//  diagrams/flow1.png
    Object *string__len__ = new_string(LEN, NULL);
    Object *string__len__value__len__ = new_integer(strlen(LEN));
    Object *string__name__ = new_string(NAME, NULL);
    Object *string__name__value__len__ = new_integer(strlen(NAME));

    Object *string__name__field__len__ = new_field(NULL, string__name__value__len__);
    Object *string__len__field__len__ = new_field(NULL, string__len__value__len__);
    Object *field__len__field__name__ = new_field(NULL, string__len__);
    __global__field__name__field__name__ = new_field(NULL, string__name__);

    append_field(string__name__field__len__, field__len__field__name__);
    append_field(string__len__field__len__, field__len__field__name__);
    append_field(field__len__field__name__, __global__field__name__field__name__);
    append_field(__global__field__name__field__name__, __global__field__name__field__name__);

    println(string__len__);
    println(string__len__value__len__);
    println(string__name__);
    println(string__name__value__len__);

    println(string__name__field__len__);
    println(string__len__field__len__);
    println(field__len__field__name__);
    println(__global__field__name__field__name__);
}