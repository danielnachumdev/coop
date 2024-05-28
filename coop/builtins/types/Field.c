//
// Created by t-danachum on 27/05/2024.
//

#include <memory.h>
#include "../../globals.h"

Object *Field = NULL;

void __init_field(void) {
    Field = new_object(Type);
}

Object *new_field_explicit(Object *name_field, Object *value) {
    Object *res = new_object(Field);
    append_field(res, name_field);
    res->data = value;
    return res;
}

Object *new__name__field(const char *name) {
    if (__global__field__name__field__name__ == NULL) return NULL;
    Object *res = new_field_explicit(
            __global__field__name__field__name__,
            new_string_explicit(
                    name,
                    new__len__field(strlen(name))
            )
    );
    return res;
}

Object *new__len__field(unsigned long n) {
    if (__global__field__len__field__name__ == NULL) return NULL;
    Object *res = new_field_explicit(
            __global__field__len__field__name__,
            new_integer(n)
    );
    return res;
}

void append_field(Object *obj, Object *field) {
    if (obj == NULL || field == NULL) return;
    Object **new_attrs = acquire(sizeof(Object *) * (obj->num_attributes + 1));
    if (obj->attributes != NULL) {
        memcpy(new_attrs, obj->attributes, sizeof(Object *) * obj->num_attributes);
        release(obj->attributes);
    }
    obj->attributes = new_attrs;
    obj->attributes[obj->num_attributes] = field;
    obj->num_attributes += 1;
}