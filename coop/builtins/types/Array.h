//
// Created by danie on 28/05/2024.
//

#ifndef COOP_ARRAY_H
#define COOP_ARRAY_H


#include "../object.h"
#include "../functions/len.h"
#include "../macros.h"

void __init_array(void);

DECLARE(Array, __init__, Object *, IndexT num_objects, Object *items_type);

DECLARE(Array, __getitem__, Object *, const Object *arr, IndexT index);

DECLARE(Array, __setitem__, void, Object *arr, IndexT index, Object *value);

DECLARE(Array, __contains__, bool, const Object *arr, const Object *obj);

DECLARE(Array, __eq__, bool, const Object *a, const Object *b);

DECLARE(Array, __print__, void, const Object *arr);

DECLARE(Array, __len__, Object *, const Object *self);


#endif //COOP_ARRAY_H
