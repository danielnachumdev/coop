//
// Created by danie on 28/05/2024.
//

#include <string.h>
#include "setattr.h"
#include "getattr.h"
#include "../../types/Field.h"
#include "../../types/String.h"
#include "../../types/Integer.h"

void setattr(Object *obj, const char *name, Object *value) {
    Object *existing = getattr(obj, name);
    if (existing == NULL) {
        Object *name_field_length = new_integer(strlen(name));
        Object *name_field = new_string_explicit(name, name_field_length);
        Object *f = new_field_explicit(name_field, value);
        append_field(obj, f);
    } else {

    }
}