//
// Created by t-danachum on 27/05/2024.
//

#include <memory.h>
#include "Field.h"
#include "../../memory/allocator.h"

Object *Field = NULL;

void init_field(void) {
    Field = acquire(sizeof(Object));
    *Field = init_object(Type);
}

Object *new_field(Object *name_field, Object *value) {
    Object *res = new_object(Field);
    append_field(res, name_field);
    res->data = value;
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