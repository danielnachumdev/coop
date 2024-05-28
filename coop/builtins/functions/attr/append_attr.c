//
// Created by danie on 28/05/2024.
//

#include <memory.h>
#include "append_attr.h"
#include "../../../memory/allocator.h"

void append_attr(Object *obj, Object *attr) {
    if (obj == NULL || attr == NULL) return;
    Object **new_attrs = acquire(sizeof(Object *) * (obj->num_attributes + 1));
    if (obj->attributes != NULL) {
        memcpy(new_attrs, obj->attributes, sizeof(Object *) * obj->num_attributes);
        release(obj->attributes);
    }
    obj->attributes = new_attrs;
    obj->attributes[obj->num_attributes] = attr;
    obj->num_attributes += 1;
}