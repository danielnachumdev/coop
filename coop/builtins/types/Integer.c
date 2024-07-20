//
// Created by t-danachum on 27/05/2024.
//

#include "Integer.h"
#include "../../globals/__init__.h"

Object *Integer = NULL;

void __init_integer(void) {
    Integer = new_object(Number);
}


Object *new_integer(long long int n) {
    Object *res = new_object(Integer);
    if (res == NULL) return NULL;
    res->data = acquire(sizeof(long long int));
    if (res->data == NULL) {
        release(res);
        return NULL;
    }
    *((long long int *) res->data) = n;
    return res;
}

bool integer_equals(const Object *a, const Object *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (not(a->type == b->type)) return false;
    if (not(a->type == Integer)) return false;
    return *cast(a->data, long long int *) == *cast(b->data, long long int *);
}