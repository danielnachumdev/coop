//
// Created by danie on 28/05/2024.
//


#include "../object.h"
#include "../../memory/allocator.h"
#include "../macros.h"
#include "../constants.h"
#include "../functions/attr/getattr.h"
#include "../functions/print.h"
#include "../functions/attr/setattr.h"
#include "Integer.h"
#include "String.h"

Object *Array = NULL;

void __init_array(void) {
    Array = new_object(Type);
}

long long array_length(const Object *arr) {
    return *cast(getattr(arr, LEN)->data, long long *);
}

Object *new_array(unsigned int num_objects, Object *items_type) {
    Object *res = new_object(Array);
    if (res == NULL) return NULL;
    res->attributes = acquire(sizeof(Attribute) * 3);
    if (res->attributes == NULL) return NULL;
    res->num_attributes = 3;
    Attribute len_field = new_attr(LEN, new_integer(num_objects));
    Attribute name_field = new_attr(NAME, new_string("Array"));
    Attribute item_type_field = new_attr(TYPE, items_type);
    res->attributes[0] = len_field;
    res->attributes[1] = name_field;
    res->attributes[2] = item_type_field;
    res->data = acquire(sizeof(Object *) * num_objects);
    return res;
}

Object *array_get(const Object *arr, unsigned int index) {
    if (arr == NULL) return NULL;
    long long length = array_length(arr);
    if (length <= index) return NULL;
    return cast(arr->data, Object **)[index];
}

void array_set(Object *arr, unsigned int index, Object *value) {
    if (arr == NULL) return;
    long long length = array_length(arr);
    if (length <= index) return;
    cast(arr->data, Object **)[index] = value;
}

bool array_contains(const Object *arr, const Object *obj) {
    if (arr == NULL || obj == NULL) return false;
    long long length = array_length(arr);
    for (long long i = 0; i < length; ++i)
        if (object_equals(obj, array_get(arr, i))) return true;

    return false;
}

bool array_equals(const Object *a, const Object *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (not(a->type == b->type)) return false;
    if (not(a->type == Array)) return false;
    Object *len;
    if (not(object_equals(len = getattr(a, LEN), getattr(b, LEN)))) return false;
    for (unsigned int i = 0; i < *cast(len->data, unsigned int *); ++i)
        if (not(object_equals(array_get(a, i), array_get(b, i)))) return false;
    return true;
}

void array_print(const Object *arr) {
    printf("[");
    Object *length_attr = getattr(arr, LEN);
    if (length_attr != NULL)
        __print_object(array_get(arr, 0));
    long long length = array_length(arr);
    for (unsigned int i = 1; i < length; ++i) {
        printf(", ");
        __print_object(array_get(arr, i));
    }
    printf("]");
}

