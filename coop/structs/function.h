//
// Created by danie on 18/05/2024.
//

#ifndef MACROPYTHON_FUNCTION_H
#define MACROPYTHON_FUNCTION_H

#include "optional.h"

struct Type;
struct Field;
typedef struct Function {
    struct Type *return_type;
    char *name;

    void *(*impl)();

    unsigned int num_args;
    struct Type **arg_types;
    unsigned int num_fields;
    struct Field **fields;
    unsigned int num_functions;
    struct Function **functions;
} Function;

Optional new_function_impl(
        struct Type *return_type,
        const char *name,
        void *(*impl)(),
        unsigned int num_args,
        unsigned int num_fields,
        unsigned int num_functions,
        ...
);

#define new_function(name) new_function_impl(NULL,name,NULL,0,0,0)

#endif //MACROPYTHON_FUNCTION_H
