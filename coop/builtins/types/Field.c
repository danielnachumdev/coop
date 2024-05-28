//
// Created by t-danachum on 27/05/2024.
//

#include "Field.h"
#include "../../memory/allocator.h"
#include "../functions/attr/append_attr.h"

Object *Field = NULL;

void init_field(void) {
    Field = acquire(sizeof(Object));
    *Field = init_object(Type);
}

Object *new_field(Object *name_field, Object *value) {
    Object *res = new_object(Field);
    append_attr(res, name_field);
    res->data = value;
    return res;
}