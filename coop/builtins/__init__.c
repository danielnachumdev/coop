//
// Created by t-danachum on 27/05/2024.
//

#include "__init__.h"
#include "Integer.h"
#include "String.h"
#include "Type.h"
#include "Number.h"

void init_builtins(void) {
    init_type();
    init_number();
    init_string();
    init_integer();
}