//
// Created by t-danachum on 27/05/2024.
//

#include "Function.h"
#include "__init__.h"

#include "../macros.h"
#include "../functions/attr/setattr.h"

Object *Function = NULL;

Object *__new_function(const char *name, void *(*impl)(), Object *return_type, Object *arguments_array) {
    if (name == NULL || impl == NULL) return NULL;
    Object *res = new_object(Function);
    if (res == NULL) return NULL;

    setattr(res, "__name__",
            __new_string(name)); //should be explicitly __new_string because of __init_string that uses __new_function
    setattr(res, "__return__", return_type);
    setattr(res, "__args__", arguments_array);

    res->data = impl;
    return res;
}

void __init_function(void) {
    Function = new_object(Type);
    setattr(Function, "__name__", __new_string("Function"));
    explicitsetfunc(Function, __print__);
    explicitsetfunc(Function, __eq__);
    explicitsetfunc(Function, __init__);
}


DEF(Function, __init__, Object *, {
    return __new_function(name, impl, return_type, arguments_array);
}, const char *name, void *(*impl)(), Object *return_type, Object *arguments_array);

DEF(Function, __print__, void, {
    if (self == NULL) return;
    if (self->type != Function) return;
    printf("Function @ %p", self->data);
}, const Object *self);

DEF(Function, __eq__, bool, {
    if (self == NULL && other == NULL) return true;
    if (not(self != NULL && other != NULL)) return false;
    if (not(self->type == other->type)) return false;
    if (not(self->type == Function)) return false;
    Object *ret1 = getattr(self, "__return__");
    Object *ret2 = getattr(other, "__return__");
    if ((ret1 == NULL ^ ret2 == NULL) == true) return false;
    if (not(cast(getattr(ret1, "__eq__")->data, bool(*)(const Object*, const Object*))(ret1, ret2))) return false;
    Object *args1 = getattr(self, "__args__");
    Object *args2 = getattr(other, "__args__");
    if ((args1 == NULL ^ args2 == NULL) == true) return false;
    if (not(cast(getattr(args1, "__eq__")->data, bool(*)(const Object*, const Object*))(args1, args2))) return false;
    return true;
}, const Object *self, const Object *other)