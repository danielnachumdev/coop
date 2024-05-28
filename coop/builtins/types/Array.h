//
// Created by danie on 28/05/2024.
//

#ifndef COOP_ARRAY_H
#define COOP_ARRAY_H

#include "../../globals.h"

void __init_array(void);

Object *new_array(unsigned int num_objects, Object *items_type);

Object *array_get(const Object *arr, unsigned int index);

void array_set(Object *arr, unsigned int index, Object *value);

bool array_contains(const Object *arr, const Object *obj);

bool array_equals(const Object *a, const Object *b);

#endif //COOP_ARRAY_H
