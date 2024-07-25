//
// Created by danie on 28/05/2024.
//

#include <string.h>
#include <stdarg.h>
#include "../../object.h"
#include "../../macros.h"
#include "__attr_utils.h"

Object *_getattr(const Object *obj, const char *key, unsigned int num_args, ...) {
    if (obj == NULL) return NULL;
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
    unsigned int index = 0;
    if (not(get_attr_index(obj, key, &index))) {
        if (obj->type == Type)
            return default_return_value;
        return _getattr(obj->type, key, 1, default_return_value);
    }
    return obj->attributes[index]->value;
}