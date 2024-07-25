//
// Created by danie on 28/05/2024.
//

#include <stdarg.h>
#include "Union.h"
#include "__init__.h"
#include "../functions/isinstance.h"
#include "../functions/print.h"
#include "../../memory/allocator.h"

Object *Union = NULL;

void __init_union(void) {
    Union = new_object(Type);
    setattr(Union, "__name__", __new_string("Union"));
    explicitsetfunc(Union, __init__);
    explicitsetfunc(Union, __contains__);
    explicitsetfunc(Union, __eq__);
    explicitsetfunc(Union, __print__);
    explicitsetfunc(Union, __len__);
}

DEF(Union, __init__, Object*, {
    Object *res = new_object(Union);
    if (res == NULL) return NULL;

    res->data = explicitgetfunc(Array, __init__)(num_types, Type);
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
        explicitgetfunc(Array, __setitem__)(res->data, i, cur);
    }
    va_end(valist);
    return res;
}, IntegerT num_types, ...);

DEF(Union, __contains__, bool, {
    if (union_ == NULL || T == NULL) return false;
    return explicitgetfunc(Array, __contains__)(union_->data, T);
}, const Object *union_, const Object *T);

DEF(Union, __eq__, bool, {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (not(a->type == b->type)) return false;
    if (not(a->type == Union)) return false;
    long long length1 = len(a->data);
    long long length2 = len(b->data);
    if (not(length1 == length2)) return false;
    Union__contains___prototype inu = Union__contains__;
    Array__getitem___prototype at = Array__getitem__;
    for (long long i = 0; i < length1; ++i)
        if (not(inu(b, at(a->data, i)))) return false;
    for (long long i = 0; i < length2; ++i)
        if (not(inu(a, at(b->data, i)))) return false;
    return true;
}, const Object *a, const Object *b);

DEF(Union, __print__, void, {
    printf("Union(");
    __print_object(obj->data);
    printf(")");
}, const Object *obj);

DEF(Union, __len__, Object*, {
    if (obj == NULL) return explicitgetfunc(Integer, __init__)(0L);
    return explicitgetfunc(Array, __len__)(obj->data);
}, const Object *obj);