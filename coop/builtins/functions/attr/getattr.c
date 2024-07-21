//
// Created by danie on 28/05/2024.
//

#include <string.h>
#include <stdarg.h>
#include "../../object.h"
#include "../../macros.h"

Object *_getattr(const Object *obj, const char *key, unsigned int num_args, ...) {
    Object *default_return_value = NULL;
    if (num_args > 0) {
        if (num_args > 1)
            printf("\nWarning: getattr(obj,key,default) does not use more that one optional argument\n");
        va_list valist;
        va_start(valist, 1);
        default_return_value = va_arg(valist, Object *);
        va_end(valist);
    }
    if (obj == NULL || key == NULL) return default_return_value;
    for (unsigned long i = 0; i < obj->num_attributes; ++i) {
        Object *attr = obj->attributes[i];
        if (not(attr->type == Field)) continue;
        for (unsigned long j = 0; j < attr->num_attributes; ++j) {
            Object *sub_attr = attr->attributes[j];
            if (not(sub_attr->type == Field)) continue;
            if (not(cast(sub_attr->data, Object * )->type == String)) continue;
            const char *attr_name = ((char *) ((Object *) sub_attr->data)->data);
//            const void *attr_value = ((void *) ((Object *) attr->data)->data);
            if (strcmp(attr_name, key) != 0) continue;
            return attr;
        }
    }
    return default_return_value;
}