//
// Created by t-danachum on 27/05/2024.
//

#include <stdio.h>
#include "Number.h"
#include "../object.h"
#include "../../memory/allocator.h"
#include "../functions/print.h"
#include "../functions/attr/getattr.h"
#include "../functions/attr/setattr.h"
#include "String.h"


Object *Number = NULL;

void __init_number(void) {
    Number = new_object(Type);
    setattr(Number, "__name__", new_string("Number"));
}

bool number_equals(const Object *a, const Object *b) {
    return false;
}

void number_print(const Object *obj) {
    printf("Type(Subtype=Number, name=");
    __print_object(getattr(obj, "__name__"));
    printf(")");
}