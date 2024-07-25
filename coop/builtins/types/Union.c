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
}

Object *new_union(IndexT num_types, ...) {
    Object * res = new_object(Union);
    if (res == NULL) return NULL;

    res->data = explicitgetfunc(Array, __init__)(num_types, Type);
    if (res->data == NULL) {
        release(res);
        return NULL;
    }

    va_list valist;
    va_start(valist, num_types);
    for (unsigned int i = 0; i < num_types; ++i) {
        Object * cur = va_arg(valist, Object *);
        if (not(isinstance(cur, Type))) {
            release(res->data);
            release(res);
            return NULL;
        }
        explicitgetfunc(Array, __setitem__)(res->data, i, cur);
    }
    va_end(valist);
    return res;
}

bool union_contains(const Object *union_, const Object *T) {
    if (union_ == NULL || T == NULL) return false;
    return explicitgetfunc(Array, __contains__)(union_->data, T);
}

bool union_equals(const Object *a, const Object *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (not(a->type == b->type)) return false;
    if (not(a->type == Union)) return false;
    long long length1 = len(a->data);
    long long length2 = len(b->data);
    if (not(length1 == length2)) return false;
    for (long long i = 0; i < length1; ++i)
        if (not(union_contains(b, explicitgetfunc(Array, __getitem__)(a->data, i)))) return false;
    for (long long i = 0; i < length2; ++i)
        if (not(union_contains(a, explicitgetfunc(Array, __getitem__)(b->data, i)))) return false;
    return true;
}

void union_print(const Object *obj) {
    printf("Union(");
    __print_object(obj->data);
    printf(")");
}