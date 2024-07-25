//
// Created by danie on 28/05/2024.
//

#include <string.h>
#include "../../object.h"
#include "getattr.h"
#include "../../types/__init__.h"
#include "../../../memory/__init__.h"
#include "__attr_utils.h"


void setattr(Object *obj, const char *key, Object *value) {
    if (obj == NULL || key == NULL || value == NULL)return;
    unsigned int index = 0;
    if (get_attr_index(obj, key, &index)) {
        obj->attributes[index]->value = value;
        return;
    }
    Attribute **new_attrs = acquire(sizeof(Attribute *) * (obj->num_attributes + 1));
    if (new_attrs == NULL) return;
    if (obj->attributes != NULL) {
        memcpy(new_attrs, obj->attributes, sizeof(Attribute*) * obj->num_attributes);
        release(obj->attributes);
    }
    obj->attributes = new_attrs;
    obj->attributes[obj->num_attributes] = new_attr(key, value);
    obj->num_attributes += 1;
}