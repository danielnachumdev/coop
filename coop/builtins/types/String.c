//
// Created by t-danachum on 27/05/2024.
//

#include <string.h>
#include "String.h"
#include "../../memory/__init__.h"
#include "../macros.h"
#include "__init__.h"
#include "../functions/attr/setattr.h"


Object *String = NULL;

Object *__new_string(const char *s) {
    Object *res = new_object(String);
    if (res == NULL) return NULL;
    setattr(res, "__len__", __new_integer((IntegerT) strlen(s)));
    if (s != NULL) {
        res->data = acquire(strlen(s) + 1);
        strcpy(res->data, s);
    }
    return res;
}

DEF(String, __init__, Object*, {
    return __new_string(s);
}, const char *s)

DEF(String, __eq__, bool, {
    if (self == NULL && other == NULL) return true;
    if (self == NULL || other == NULL) return false;
    if (not(self->type == other->type)) return false;
    if (not(self->type == String)) return false;
    return strcmp(self->data, other->data) == 0;
}, const Object *self, const Object *other)

DEF(String, __print__, void, {
    if (self == NULL) return;
    printf("%s", cast(self->data,
    char *));
}, const Object *self)

DEF(String, __bool__, bool, {
    if (self == NULL) return false;
    return len(self) > 0;
}, const Object *self);

void __init_string(void) {
    String = new_object(Type);
    setattr(String, "__name__", __new_string("String"));
}

void __init_string_functions(void) {
    isetfunc(String, __init__);
    isetfunc(String, __print__);
    isetfunc(String, __eq__);
    isetfunc(String, __bool__);
}
