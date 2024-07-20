//
// Created by t-danachum on 27/05/2024.
//

#include <string.h>
#include "../object.h"
#include "../append_attr.h"
#include "String.h"
#include "../../memory/allocator.h"
#include "Integer.h"
#include "../__init__.h"

Object *Field = NULL;

void __init_field(void) {
    Field = new_object(Type);
}

Object *new_field_explicit(Object *name_field, Object *value) {
    Object *res = new_object(Field);
    if (res == NULL)
        return NULL;
//    explicitly do not validate append_attr succeeds because this is an explicit call
    append_attr(res, name_field);
    res->data = value;
    return res;
}

Object *new__name__field(const char *name) {
    if (__global__field__name__field__name__ == NULL) return NULL;
    Object *len_field = new__name__field(strlen(name));
    if (len_field == NULL) return NULL;
    Object *name_object = new_string_explicit(name, len_field);
    if (name_object == NULL) {
        release(len_field);
        return NULL;
    }
    Object *res = new_field_explicit(__global__field__name__field__name__, name_object);
    if (res == NULL) {
        release(len_field);
        release(name_object);
    }
    return res;
}

Object *new__len__field(unsigned long n) {
    if (__global__field__len__field__name__ == NULL) return NULL;
    Object *value = new_integer(n);
    if (value == NULL) return NULL;
    Object *res = new_field_explicit(__global__field__len__field__name__, value);
    return res;
}

Object *new_field(const char *name, Object *value) {
    Object *name_field = new__name__field(name);
    if (name_field == NULL) return NULL;
    Object *res = new_field_explicit(name_field, value);
    return res;
}