//
// Created by danie on 28/05/2024.
//

#include "Array.h"
#include "../../memory/allocator.h"
#include "../macros.h"
#include "../functions/attr/getattr.h"
#include "../functions/print.h"
#include "../functions/attr/setattr.h"
#include "Integer.h"
#include "String.h"

Object *Array = NULL;

void __init_array(void) {
    Array = new_object(Type);
    setattr(Array, "__name__", new_string("Array"));
}

Object *new_array(IndexT num_objects, Object *items_type) {
    Object *res = new_object(Array);
    if (res == NULL) return NULL;
    res->attributes = acquire(sizeof(Attribute) * 3);
    if (res->attributes == NULL) return NULL;
    res->num_attributes = 3;
    Attribute *len_field = new_attr("__len__", new_integer(num_objects));
    Attribute *name_field = new_attr("__name__", new_string("Array"));
    Attribute *item_type_field = new_attr("__type__", items_type);
    res->attributes[0] = len_field;
    res->attributes[1] = name_field;
    res->attributes[2] = item_type_field;
    res->data = acquire(sizeof(Object *) * num_objects);
    return res;
}

Object *array_get(const Object *arr, IndexT index) {
    if (arr == NULL) return NULL;
    IndexT length = len(arr);
    if (length <= index) return NULL;
    return cast(arr->data, Object **)[index];
}

void array_set(Object *arr, IndexT index, Object *value) {
    if (arr == NULL) return;
    IndexT length = len(arr);
    if (length <= index) return;
    cast(arr->data, Object **)[index] = value;
}

bool array_contains(const Object *arr, const Object *obj) {
    if (arr == NULL || obj == NULL) return false;
    IndexT length = len(arr);
    for (IndexT i = 0; i < length; ++i)
        if (object_equals(obj, array_get(arr, i))) return true;

    return false;
}

bool array_equals(const Object *a, const Object *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (not(a->type == b->type)) return false;
    if (not(a->type == Array)) return false;
    Object *len;
    if (not(object_equals(len = getattr(a, "__len__"), getattr(b, "__len__")))) return false;
    for (IndexT i = 0; i < *cast(len->data, IndexT *); ++i)
        if (not(object_equals(array_get(a, i), array_get(b, i)))) return false;
    return true;
}

void array_print(const Object *arr) {
    printf("[");
    Object *length_attr = getattr(arr, "__len__");
    if (length_attr != NULL)
        __print_object(array_get(arr, 0));
    IndexT length = len(arr);
    for (IndexT i = 1; i < length; ++i) {
        printf(", ");
        __print_object(array_get(arr, i));
    }
    printf("]");
}

