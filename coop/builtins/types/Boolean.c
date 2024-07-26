//
// Created by danie on 28/05/2024.
//

#include "Boolean.h"
#include "../../memory/allocator.h"
#include "String.h"
#include "Integer.h"
#include "Function.h"

Object *Boolean = NULL;

void __init_boolean(void) {
    Boolean = new_object(Type);
    setattr(Boolean, "__name__", __new_string("Boolean"));
    implicitsetfunc(Boolean, __init__);
    implicitsetfunc(Boolean, __eq__);
    implicitsetfunc(Boolean, __print__);
    implicitsetfunc(Boolean, __int__);
    implicitsetfunc(Boolean, __bool__);
}

DEF(Boolean, __init__, Object *, {
    Object *res = new_object(Boolean);
    if (res == NULL) return NULL;
    res->data = acquire(sizeof(bool));
    if (res->data == NULL) {
        release(res);
        return NULL;
    }
    *cast(res->data, bool * ) = v;
    return res;
}, const bool v);

DEF(Boolean, __eq__, bool, {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (not(a->type == b->type)) return false;
    if (not(a->type == Boolean)) return false;
    return *cast(a->data, bool * ) == *cast(b->data, bool * );
}, const Object *a, const Object *b);

DEF(Boolean, __print__, void, {
    printf("%s", *cast(obj->data, bool * ) ? "true" : "false");
}, const Object *obj);

DEF(Boolean, __int__, Object *, {
    if (obj == NULL) return NULL;
    IntegerT i = *((int *) obj->data) ? 1L : 0L;
    return implicitgetfunc(Integer, __init__)(i);
}, const Object *obj);

DEF(Boolean, __bool__, Object *, {
    if (self == NULL) return NULL;
    return implicitgetfunc(Boolean, __init__)(*cast(self->data, bool * ));
}, const Object *self);