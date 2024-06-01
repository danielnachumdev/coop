
//
// Created by danie on 02/06/2024.
//

#include "dir.h"
#include "../../builtins/types/__init__.h"

Object *dir(const Object *obj) {
    if (obj == NULL) return NULL;
    Object *res = new_array(obj->num_attributes, new_union(2, Field, Function));
    for (unsigned int i = 0; i < obj->num_attributes; ++i) {
        array_set(res, i, obj->attributes[i]);
    }
    return res;
}