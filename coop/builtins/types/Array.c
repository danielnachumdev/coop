//
// Created by danie on 28/05/2024.
//

#include "Array.h"
#include "../../memory/allocator.h"
#include "../functions/globals/print.h"
#include "Integer.h"
#include "String.h"
#include "Function.h"

Object *Array = NULL;

void __init_array(void) {
    Array = new_object(Type);
    setattr(Array, "__name__", __new_string("Array"));
    implicitsetfunc(Array, __init__);
    implicitsetfunc(Array, __getitem__);
    implicitsetfunc(Array, __setitem__);
    implicitsetfunc(Array, __contains__);
    implicitsetfunc(Array, __eq__);
    implicitsetfunc(Array, __print__);
    implicitsetfunc(Array, __len__);
}

DEF(Array, __init__, Object *, {
    Object *res = new_object(Array);
    if (res == NULL) return NULL;
    res->attributes = acquire(sizeof(Attribute) * 3);
    if (res->attributes == NULL) return NULL;
    res->num_attributes = 3;
    Attribute *len_field = new_attr("__len__", implicitgetfunc(Integer, __init__)(num_objects));
    Attribute *name_field = new_attr("__name__", __new_string("Array"));
    Attribute *item_type_field = new_attr("__type__", items_type);
    res->attributes[0] = len_field;
    res->attributes[1] = name_field;
    res->attributes[2] = item_type_field;
    res->data = acquire(sizeof(Object *) * num_objects);
    return res;
}, IndexT num_objects, Object *items_type)

DEF(Array, __getitem__, Object *, {
    if (arr == NULL) return NULL;
    IndexT length = len(arr);
    if (length <= index) return NULL;
    return cast(arr->data, Object * *)[index];
}, const Object *arr, IndexT index)

DEF(Array, __setitem__, void, {
    if (arr == NULL) return;
    IndexT length = len(arr);
    if (length <= index) return;
    cast(arr->data, Object * *)[index] = value;
}, Object *arr, IndexT index, Object *value)

DEF(Array, __contains__, bool, {
    if (arr == NULL || obj == NULL) return false;
    IndexT length = len(arr);
    for (IndexT i = 0; i < length; ++i)
        if (object_equals(obj, implicitgetfunc(Array, __getitem__)(arr, i))) return true;

    return false;
}, const Object *arr, const Object *obj)

DEF(Array, __eq__, bool, {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (not(a->type == b->type)) return false;
    if (not(a->type == Array)) return false;
    Object *len;
    if (not(object_equals(len = getattr(a, "__len__"), getattr(b, "__len__")))) return false;
    for (IndexT i = 0; i < *cast(len->data, IndexT * ); ++i)
        if (not(object_equals(implicitgetfunc(Array, __getitem__)(a, i),
                              implicitgetfunc(Array, __getitem__)(b, i))))
            return false;
    return true;
}, const Object *a, const Object *b)

DEF(Array, __print__, void, {
    printf("[");
    Object *length_attr = getattr(arr, "__len__");
    if (length_attr != NULL)
        __print_object(implicitgetfunc(Array, __getitem__)(arr, 0));
    IndexT length = len(arr);
    for (IndexT i = 1; i < length; ++i) {
        printf(", ");
        __print_object(implicitgetfunc(Array, __getitem__)(arr, i));
    }
    printf("]");
}, const Object *arr)

DEF(Array, __len__, Object *, {
    if (self == NULL) return 0;
    IntegerT res = *cast(getattr(self, "__len__")->data, IntegerT * );
    return implicitgetfunc(Integer, __init__)(res);
}, const Object *self)