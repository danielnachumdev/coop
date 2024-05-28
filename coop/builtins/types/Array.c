//
// Created by danie on 28/05/2024.
//

#include "Array.h"

Object *Array = NULL;

void __init_array(void) {
    Array = new_object(Type);
}

Object *new_array(unsigned int num_objects, Object *items_type) {
    Object *res = new_object(Array);
    if (res == NULL) return NULL;
    Object *len_field = new__len__field(num_objects);
    if (len_field == NULL) {
        release(res);
        return NULL;
    }
    if (not(append_attr(res, len_field))) {
        release(res);
        release(len_field);
        return NULL;
    }
    Object *name_field = new__name__field(TYPE);
    if (name_field == NULL) {
        release(res);
        release(len_field);
        return NULL;
    }
    Object *type_field = new_field_explicit(name_field, items_type);
    if (type_field == NULL) {
        release(res);
        release(len_field);
        release(name_field);
        return NULL;
    }
    if (not(append_attr(res, type_field))) {
        release(res);
        release(len_field);
        release(name_field);
        release(type_field);
        return NULL;
    }
    res->data = acquire(sizeof(Object *) * num_objects);
    if (res->data == NULL) {
        release(res);
        release(len_field);
        release(name_field);
        release(type_field);
        return NULL;
    }
    return res;
}

Object *array_get(Object *arr, unsigned int index) {
    if (arr == NULL) return NULL;
    Object *length = getattr(arr, LEN);
    if (*cast(length, unsigned int *) <= index) return NULL;
    return cast(arr->data, Object**)[index];
}

void array_set(Object *arr, unsigned int index, Object *value) {
    if (arr == NULL) return;
    Object *length = getattr(arr, LEN);
    if (*cast(length, unsigned int *) <= index) return;
    cast(arr->data, Object**)[index] = value;
}