//
// Created by danie on 18/05/2024.
//

#ifndef MACROPYTHON_FIELD_H
#define MACROPYTHON_FIELD_H

#include "optional.h"

struct Type;
struct Function;
typedef struct Field {
    struct Type *type;
    char *name;
    void *value;
    unsigned int num_fields;
    struct Field **fields;
    unsigned int num_functions;
    struct Function **functions;

    void *(*get)(struct Type *t);

    Optional (*str)(struct Field *t);
} Field;

Optional new_field_impl(
        struct Type *T,
        const char *name,
        void *initial_value,
        unsigned int num_fields,
        unsigned int num_functions,
        ...
);

#define new_field(T, name, initial_value, num_fields, num_functions, ...) new_field_impl(T,name,initial_value,num_fields,num_functions, ## __VA_ARGS__)
#endif //MACROPYTHON_FIELD_H
