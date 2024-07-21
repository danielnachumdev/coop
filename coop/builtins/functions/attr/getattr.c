//
// Created by danie on 28/05/2024.
//

#include <string.h>
#include "../../object.h"
#include "../../macros.h"
#include "../../constants.h"

Object *getattr(const Object *obj, const char *name) {
    if (obj == NULL || name == NULL) return NULL;
    for (unsigned long i = 0; i < obj->num_attributes; ++i) {
        Object *attr = obj->attributes[i];
        if (not(attr->type == Field)) continue;
        for (unsigned long j = 0; j < attr->num_attributes; ++j) {
            Object *sub_attr = attr->attributes[j];
            if (not(sub_attr->type == Field)) continue;
            if (not(cast(sub_attr->data, Object * )->type == String)) continue;
            const char *attr_name = ((char *) ((Object *) sub_attr->data)->data);
            const void *attr_value = ((void *) ((Object *) attr->data)->data);
            if (strcmp(attr_name, name) != 0) continue;
            return attr;
        }
    }
    return NULL;
}