//
// Created by danie on 28/05/2024.
//

#include <string.h>
#include "../../object.h"
#include "getattr.h"
#include "../../types/__init__.h"
#include "../../append_attr.h"

void setattr(Object *obj, const char *name, Object *value) {
    Object *existing = getattr(obj, name);
    if (existing == NULL) {
        Object *name_field_length = new_integer((long long) strlen(name));
        Object *name_field = new_string_explicit(name, name_field_length);
        Object *f = new_field_explicit(name_field, value);
        append_attr(obj, f);
    } else {

    }
}