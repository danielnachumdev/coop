
//
// Created by danie on 02/06/2024.
//
#include <memory.h>
#include <stdbool.h>
#include "append_attr.h"
#include "../memory/__init__.h"

bool append_attr(Object *obj, Object *attr) {
    if (obj == NULL || attr == NULL) return false;
    Object **new_attrs = acquire(sizeof(Object *) * (obj->num_attributes + 1));
    if (new_attrs == NULL) return false;
    if (obj->attributes != NULL) {
        memcpy(new_attrs, obj->attributes, sizeof(Object *) * obj->num_attributes);
        release(obj->attributes);
    }
    obj->attributes = new_attrs;
    obj->attributes[obj->num_attributes] = attr;
    obj->num_attributes += 1;
    return true;
}
