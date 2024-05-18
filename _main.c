//
// Created by danie on 17/05/2024.
//

#include "_main.h"
#include "coop/structs/type.h"
#include "coop/structs/field.h"
#include "coop/structs/function.h"
#include "coop/print.h"

#define __CREATE_GETTER(RET_T, INST_T, x) \
RET_T * PASTE3(INST_T,_get_,RET_T) (INST_T * o, const char * name){ \
    if (o == NULL || name == NULL) return NULL;\
    for (unsigned int i = 0; i < o->PASTE2(num_,x); ++i)\
        if (strcmp(o->x[i]->name, name) == 0) return o->x[i];\
    return NULL;                              \
}

__CREATE_GETTER(Field, Field, fields)

__CREATE_GETTER(Field, Function, fields)

__CREATE_GETTER(Field, Type, fields)

__CREATE_GETTER(Function, Field, functions)

__CREATE_GETTER(Function, Function, functions)

__CREATE_GETTER(Function, Type, functions)


#define GET(RET_T, INST_T, obj, key) PASTE3(INST_T,_get_,RET_T)(obj,key)

void _main(void) {
    Type *Integer = new_type("Integer", 0, 0).nullable;
    Type *String = new_type("String", 0, 0).nullable;
    int default_length_value = 0;
    Field *string_length = new_field_impl(
            Integer,
            "Length",
            &default_length_value,
            0,
            0
    ).nullable;
    Function *integer_to_string = new_function_impl(
            String,
            "toString",
            NULL,
            1,
            0,
            0,
            Integer
    ).nullable;
    Integer->functions = acquire(sizeof(*Integer->functions)).nullable;
    Integer->functions[0] = integer_to_string;
    Field *f = GET(Field, Type, Integer, "Length");
}

