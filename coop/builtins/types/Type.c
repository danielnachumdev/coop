//
// Created by t-danachum on 27/05/2024.
//

#include <stdio.h>
#include "Type.h"
#include "Function.h"
#include "String.h"
#include "../functions/globals/print.h"

Object *Type = NULL;

void __init_type(void) {
    Type = new_object(NULL);
    Type->type = Type;
}

void __init_type_functions(void) {
    explicitsetfunc(Type, __init__);
    explicitsetfunc(Type, __print__);
    explicitsetfunc(Type, __eq__);
}

DEF(Type, __init__, Object*, {
    if (name == NULL) return NULL;
    Object *T = new_object(Type);
    setattr(T, "__name__", explicitgetfunc(String, __init__)(name));
    for (IntegerT i = 0; i < num_attributes; ++i)
        setattr(T, attrs[i].key, attrs[i].value);
    return T;
}, const char *name, IntegerT num_parents, Object parents[], IntegerT num_attributes, Attribute attrs[])

DEF(Type, __print__, void, {
    if (self == NULL)return;
    printf("Type(name=");
    __print_object(getattr(self, "__name__"));
    printf(")");
}, const Object *self)

DEF(Type, __eq__, bool, {
    return object_equals(getattr(self, "__name__"), getattr(other, "__name__"));
}, const Object *self, const Object *other)

