//
// Created by danie on 18/05/2024.
//

#ifndef MACROPYTHON_TYPE_H
#define MACROPYTHON_TYPE_H

#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "../memory_management/allocator.h"
#include "../../../../C/coop/coop/macros.h"
#include "optional.h"

struct Field;
struct Function;
typedef struct Type {
    struct Type *type;
    char *name;
    const char *file;
    unsigned int num_fields;
    struct Field **fields;
    unsigned int num_functions;
    struct Function **functions;

    Optional (*str)(struct Type *t);

    Optional (*new)();
} Type;

extern Type type_Type_impl;

Optional new_type_dispatcher(
        const char *name,
        const char *file,
        unsigned int num_fields,
        unsigned int num_functions,
        ...
);


//#define new_type(name, ...) \
//    new_type_dispatcher(    \
//    name,                   \
//    __FILE__,               \
//    NUM_POINTERS(__VA_ARGS__),   \
//    ## __VA_ARGS__   \
//    )

#define new_type(name, num_fields, num_functions, ...) \
    new_type_dispatcher(    \
    name,                   \
    __FILE__,               \
    num_fields,                                      \
    num_functions,   \
    ## __VA_ARGS__   \
    )

#define print_type(t) print(t->str(t).nullable);

#endif //MACROPYTHON_TYPE_H
