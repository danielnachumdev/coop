//
// Created by danie on 18/05/2024.
//

#include "type.h"
#include <stdarg.h>
#include "../exceptions/exception.h"
#include "../utils.h"
#include "field.h"
#include "function.h"
#include "../logging/logger.h"


Optional type_default_str_impl(Type *t) {
    Optional field_representation = {""};
    if (t->num_fields > 0)
        field_representation = t->fields[0]->str(t->fields[0]);
    for (unsigned int i = 1; i < t->num_fields; ++i) {
        RETURN_VALUE_DO_IF(field_representation.nullable == NULL, , (Optional) {NULL});
        char *next_repr = t->fields[0]->str(t->fields[i]).nullable;
        RETURN_VALUE_DO_IF(next_repr == NULL, , (Optional) {NULL});
        field_representation = concatenate_strings(
                3,
                field_representation.nullable,
                ", ",
                next_repr
        );
    }
    return concatenate_strings(
            7,
            "Type(type=", t->type->name,
            ", name=", t->name,
            ", fields=[", field_representation.nullable,
            "])"
    );
}

Optional new_type_impl(
        const char *name,
        const char *file,
        unsigned int num_fields,
        Field **fields,
        unsigned int num_functions,
        Function **functions
) {
    _DEBUG(concatenate_strings(3, "Creating new Type: ", name, "\n").nullable);
    Type *res = acquire(sizeof(Type)).nullable;
    if (res == NULL) return (Optional) {NULL};
    *res = (Type) {
            .type=&type_Type_impl,
            .name=duplicate_string(name).nullable,
            .file=file,
            .num_fields=num_fields,
            .fields=fields,
            .num_functions=num_functions,
            .functions=functions,
            .new=NULL,
            .str=type_default_str_impl,
    };
    return (Optional) {res};
}


Optional new_type_dispatcher(
        const char *name,
        const char *file,
        unsigned int num_fields,
        unsigned int num_functions,
        ...
) {
    va_list valist;
    va_start(valist, num_fields + num_functions);
    LOOP_VA_ARGS(fields, Field *, num_fields);
    LOOP_VA_ARGS(functions, Function*, num_functions);
    va_end(valist);
    return type_Type_impl.new(name, file, num_fields, fields, num_functions, functions);
}


Type type_Type_impl = (Type) {
        .type=&type_Type_impl,
        .name="Type",
        .file=__FILE__,
        .num_fields=0,
        .fields=NULL,
        .num_functions=0,
        .functions=NULL,
        .str=type_default_str_impl,
        .new= ((void *) new_type_impl)
};