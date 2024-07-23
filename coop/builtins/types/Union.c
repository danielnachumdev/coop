//
// Created by danie on 28/05/2024.
//

#include <stdarg.h>
#include "Union.h"
#include "__init__.h"
#include "../functions/isinstance.h"
#include "../macros.h"
#include "../functions/attr/getattr.h"
#include "../constants.h"
#include "../functions/print.h"
#include "../../memory/allocator.h"
#include "../functions/len.h"

Object *Union = NULL;

void __init_union(void) {
    Union = new_object(Type);
}

Object *new_union(unsigned long int num_types, ...) {
    Object *res = new_object(Union);
    if (res == NULL) return NULL;

    res->data = new_array(num_types, Type);
    if (res->data == NULL) {
        release(res);
        return NULL;
    }

    va_list valist;
    va_start(valist, num_types);
    for (unsigned int i = 0; i < num_types; ++i) {
        Object *cur = va_arg(valist, Object *);
        if (not(isinstance(cur, Type))) {
            release(res->data);
            release(res);
            return NULL;
        }
        array_set(res->data, i, cur);
    }
    va_end(valist);
    return res;
}

bool union_contains(const Object *union_, const Object *T) {
    if (union_ == NULL || T == NULL) return false;
    return array_contains(union_->data, T);
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
        if (not(union_contains(b, array_get(a->data, i)))) return false;
    for (long long i = 0; i < length2; ++i)
        if (not(union_contains(a, array_get(b->data, i)))) return false;
    return true;
}

void union_print(const Object *obj) {
    printf("Union(");
    __print_object(obj->data);
    printf(")");
}