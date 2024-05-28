//
// Created by t-danachum on 27/05/2024.
//

#include <string.h>
#include "String.h"
#include "../../memory/allocator.h"
#include "../functions/attr/append_attr.h"

Object *String = NULL;

void init_string(void) {
    String = acquire(sizeof(Object));
    *String = init_object(Type);
}

Object *new_string(const char *s, Object *length_field) {
    Object *res = new_object(String);
    append_attr(res, length_field);
    res->data = acquire(strlen(s) + 1);
    strcpy(res->data, s);
    return res;
}