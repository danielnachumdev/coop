//
// Created by t-danachum on 27/05/2024.
//

#include "Integer.h"
#include "../../memory/allocator.h"
#include "Function.h"

Object *Integer = NULL;

void __init_integer(void) {
    Integer = new_object(Number);
}

void __init_integer_functions(void) {
    explicitsetfunc(Integer, __init__);
    explicitsetfunc(Integer, __eq__);
    explicitsetfunc(Integer, __print__);
    explicitsetfunc(Integer, __bool__);
}

Object *__new_integer(IntegerT n) {
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

DEF(Integer, __init__, Object*, {
    return __new_integer(n);
}, IntegerT n);

DEF(Integer, __eq__, bool, {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (not(a->type == b->type)) return false;
    if (not(a->type == Integer)) return false;
    return *cast(a->data, IntegerT * ) == *cast(b->data, IntegerT * );
}, const Object *a, const Object *b);

DEF(Integer, __print__, void, {
    if (self == NULL) return;
    printf("%lld", *cast(self->data, IntegerT * ));
}, const Object *self);

DEF(Integer, __bool__, bool, {
    if (self == NULL) return false;
    return *cast(self->data, IntegerT * ) != 0L;
}, const Object *self);