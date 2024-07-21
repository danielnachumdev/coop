//
// Created by danie on 28/05/2024.
//

#include <string.h>
#include "../../object.h"
#include "getattr.h"
#include "../../types/__init__.h"
#include "../../../memory/__init__.h"


bool __append_attr(Object *obj, Object *attr) {
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


void setattr(Object *obj, const char *key, Object *value) {
    Object *existing = getattr(obj, key, NULL);
    if (existing == NULL) __append_attr(obj, new_field(key, value));
    else existing->data = value;
}