//
// Created by danie on 18/05/2024.
//

#include <stdarg.h>
#include "function.h"
#include "../memory_management/allocator.h"
#include "../utils.h"
#include "../logging/logger.h"
#include "../../../../C/coop/coop/macros.h"

Optional new_function_impl(
        struct Type *return_type,
        const char *name,
        void *(*impl)(),
        unsigned int num_args,
        unsigned int num_fields,
        unsigned int num_functions,
        ...
) {
    _DEBUG(concatenate_strings(3, "Creating new Function: ", name, "\n").nullable);

    va_list valist;
    va_start(valist, num_fields + num_functions + num_args);
    LOOP_VA_ARGS(args_types, struct Type*, num_args);
    LOOP_VA_ARGS(fields, struct Field*, num_fields);
    LOOP_VA_ARGS(functions, Function*, num_functions);
    va_end(valist);
    Optional res = acquire(sizeof(Function));
    if (res.nullable != NULL) {
        *((Function *) res.nullable) = (Function) {
                .return_type=return_type,
                .name=duplicate_string(name).nullable,
                .impl=impl,
                .num_args=num_args,
                .arg_types=args_types,
                .num_fields=0,
                .fields=fields,
                .num_functions=0,
                .functions=functions
        };
    }


    return res;
}