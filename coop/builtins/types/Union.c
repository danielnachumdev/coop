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

Object *Union = NULL;

void __init_union(void) {
    Union = new_object(Type);
}

Object *new_union(unsigned long int num_types, ...) {
    Object *res = new_object(Union);
    if (res == NULL) return NULL;

    res->data = new_array(num_types, Type);

    va_list valist;
    va_start(valist, num_types);
    for (unsigned int i = 0; i < num_types; ++i) {
        Object *cur = va_arg(valist, Object*);
        if (not(isinstance(cur, Type))) return NULL;
        array_set(res->data, i, cur);
    }
    va_end(valist);
    return res;
}

bool union_contains(const Object *uni, const Object *T) {
    if (uni == NULL || T == NULL) return false;
    return array_contains(uni->data, T);
}

bool union_equals(const Object *a, const Object *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (not(a->type == b->type)) return false;
    if (not(a->type == Union)) return false;
    if (not(object_equals(getattr(a->data, LEN), getattr(b->data, LEN)))) return false;
    for (unsigned int i = 0; i < *cast(getattr(a->data, LEN)->data, unsigned int *); ++i)
        if (not(union_contains(b, array_get(a->data, i)))) return false;
    for (unsigned int i = 0; i < *cast(getattr(b->data, LEN)->data, unsigned int *); ++i)
        if (not(union_contains(a, array_get(b->data, i)))) return false;
    return true;
}