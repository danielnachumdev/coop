//
// Created by danie on 28/05/2024.
//

#include "Array.h"
#include "Field.h"
#include "../../memory/allocator.h"
#include "../../globals/__init__.h"

Object *Array = NULL;

void __init_array(void) {
    Array = new_object(Type, true);
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

Object *array_get(const Object *arr, unsigned int index) {
    if (arr == NULL) return NULL;
    Object *length = getattr(arr, LEN);
    if (*cast(length, unsigned int *) <= index) return NULL;
    return cast(arr->data, Object * *)[index];
}

void array_set(Object *arr, unsigned int index, Object *value) {
    if (arr == NULL) return;
    Object *length = getattr(arr, LEN);
    if (*cast(length, unsigned int *) <= index) return;
    cast(arr->data, Object * *)[index] = value;
}

bool array_contains(const Object *arr, const Object *obj) {
    if (arr == NULL || obj == NULL) return false;
    Object *len = getattr(arr, LEN);
    for (unsigned int i = 0; i < *cast(len->data, unsigned int *);
    ++i) {
        if (object_equals(obj, array_get(arr, i))) return true;
    }
    return false;
}

bool array_equals(const Object *a, const Object *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (not(a->type == b->type)) return false;
    if (not(a->type == Array)) return false;
    Object *len;
    if (not(object_equals(len = getattr(a, LEN), getattr(b, LEN)))) return false;
    for (unsigned int i = 0; i < *cast(len->data, unsigned int *);
    ++i)
    if (not(object_equals(array_get(a, i), array_get(b, i)))) return false;
    return true;
}
