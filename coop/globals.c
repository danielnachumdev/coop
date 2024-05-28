//
// Created by danie on 28/05/2024.
//
#include <memory.h>
#include "globals.h"

bool isinstance(const Object *obj, const Object *T) {
    if (obj == NULL || T == NULL) return false;
    const Object *cur_type = obj->type;
    if (T->type == Union) {
        Object *types_array = T->data;
        Object *length = getattr(types_array, LEN);
        if (length == NULL) throw("AttributeError", "No attribute " LEN);
        for (unsigned int i = 0; i < *cast(length->data, unsigned int *); ++i)
            if (isinstance(obj, array_get(types_array, i))) return true;
    } else
        while (cur_type != Type) {
            if (cur_type == T) return true;
            cur_type = cur_type->type;
        }
    return false;
}

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

Object *dir(const Object *obj) {
    if (obj == NULL) return NULL;
    Object *res = new_array(obj->num_attributes, new_union(2, Field, Function));
    for (unsigned int i = 0; i < obj->num_attributes; ++i) {
        array_set(res, i, obj->attributes[i]);
    }
    return res;
}