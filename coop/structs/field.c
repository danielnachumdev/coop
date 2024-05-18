//
// Created by danie on 18/05/2024.
//
#include <stdarg.h>
#include "field.h"
#include "../utils.h"
#include "type.h"
#include "../logging/logger.h"

void *field_default_get_impl(Type *t) {

}


Optional field_default_str_impl(Field *f) {
    return concatenate_strings(
            5,
            "Field(type=", f->type->name,
            ", name=", f->name,
            ")"
    );
}

Optional new_field_impl(
        struct Type *T,
        const char *name,
        void *initial_value,
        unsigned int num_fields,
        unsigned int num_functions,
        ...
) {
    _DEBUG(concatenate_strings(3, "Creating new Field: ", name, "\n").nullable);
    Optional res = acquire(sizeof(Field));
    Optional dup_name = duplicate_string(name);
    if (res.nullable == NULL || dup_name.nullable == NULL) return res;
    va_list valist;
    va_start(valist, num_fields + num_functions);
    LOOP_VA_ARGS(fields, struct Field *, num_fields);
    LOOP_VA_ARGS(functions, struct Function*, num_functions);
    va_end(valist);
    *((Field *) res.nullable) = (Field) {
            .type=T,
            .name=dup_name.nullable,
            .value=initial_value,
            .num_fields=num_fields,
            .fields=fields,
            .num_functions=num_functions,
            .functions=functions,
            .get=field_default_get_impl,
            .str=field_default_str_impl,
    };
    return res;
}