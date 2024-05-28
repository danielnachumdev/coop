//
// Created by t-danachum on 27/05/2024.
//

#include <string.h>
#include "String.h"
#include "../../globals.h"

Object *String = NULL;

void __init_string(void) {
    String = new_object(Type);
}

Object *new_string_explicit(const char *s, Object *length_field) {
    Object *res = new_object(String);
    if (res == NULL) return NULL;
    append_attr(res, length_field);
    if (s != NULL) {
        res->data = acquire(strlen(s) + 1);
        strcpy(res->data, s);
    }
    return res;
}

Object *new_string(const char *s) {
    return new_string_explicit(s, new__len__field(strlen(s)));
}