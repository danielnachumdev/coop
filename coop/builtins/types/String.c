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
    setattr(res, "__len__", new_integer((long long) strlen(s)));
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

void __init_string(void) {
    String = new_object(Type);
    explicitsetfunc(String, __init__);
    explicitsetfunc(String, __eq__);
    explicitsetfunc(String, __print__);
    setattr(String, "__name__", __new_string("String"));
}


bool string_equals(const Object *a, const Object *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (not(a->type == b->type)) return false;
    if (not(a->type == String)) return false;
    return strcmp(a->data, b->data) == 0;
}

void string_print(const Object *s) {
    if (s == NULL) return;
    printf("%s", cast(s->data, char *));
}