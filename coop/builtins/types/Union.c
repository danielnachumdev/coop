//
// Created by danie on 28/05/2024.
//

#include <stdarg.h>
#include "Union.h"
#include "__init__.h"
#include "../functions/globals/isinstance.h"
#include "../functions/globals/print.h"
#include "../../memory/allocator.h"
#include "../functions/globals/contains.h"

Object *Union = NULL;

void __init_union(void) {
    Union = new_object(Type);
    setattr(Union, "__name__", __new_string("Union"));
    implicitsetfunc(Union, __init__);
    implicitsetfunc(Union, __contains__);
    implicitsetfunc(Union, __eq__);
    implicitsetfunc(Union, __print__);
    implicitsetfunc(Union, __len__);
}

DEF(Union, __init__, Object*, {
    Object *res = new_object(Union);
    if (res == NULL) return NULL;

    res->data = implicitgetfunc(Array, __init__)(num_types, Type);
    if (res->data == NULL) {
        release(res);
        return NULL;
    }

    va_list valist;
    va_start(valist, num_types);
    for (unsigned int i = 0; i < num_types; ++i) {
        Object *cur = va_arg(valist, Object * );
        if (not(isinstance(cur, Type))) {
            release(res->data);
            release(res);
            return NULL;
        }
        implicitgetfunc(Array, __setitem__)(res->data, i, cur);
    }
    va_end(valist);
    return res;
}, IntegerT num_types, ...);

DEF(Union, __contains__, bool, {
    if (self == NULL || T == NULL) return false;
    return contains(self->data, T);
}, const Object *self, const Object *T);

bool union_eq(const Object *a, const Object *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (not(a->type == b->type)) return false;
    if (not(a->type == Union)) return false;
    IndexT length1 = len(a->data);
    IndexT length2 = len(b->data);
    if (not(length1 == length2)) return false;
    Array__getitem___prototype at = Array__getitem__;
    for (long long i = 0; i < length1; ++i)
        if (not(contains(b, at(a->data, i)))) return false;
    for (long long i = 0; i < length2; ++i)
        if (not(contains(a, at(b->data, i)))) return false;
    return true;
}

DEF(Union, __eq__, bool, {
    return union_eq(a, b);
}, const Object *a, const Object *b);

DEF(Union, __print__, void, {
    printf("Union(");
    __print_object(obj->data);
    printf(")");
}, const Object *obj);

DEF(Union, __len__, Object*, {
    if (obj == NULL) return implicitgetfunc(Integer, __init__)(0L);
    return implicitgetfunc(Array, __len__)(obj->data);
}, const Object *obj);