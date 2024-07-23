//
// Created by danie on 28/05/2024.
//

#ifndef COOP_ARRAY_H
#define COOP_ARRAY_H


#include "../object.h"
#include "../functions/len.h"

void __init_array(void);

Object *new_array(IndexT num_objects, Object *items_type);

Object *array_get(const Object *arr, IndexT index);

void array_set(Object *arr, IndexT index, Object *value);

bool array_contains(const Object *arr, const Object *obj);

bool array_equals(const Object *a, const Object *b);

void array_print(const Object *arr);

long long array_length(const Object *arr);

#endif //COOP_ARRAY_H
