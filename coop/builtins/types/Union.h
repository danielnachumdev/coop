//
// Created by danie on 28/05/2024.
//

#ifndef COOP_UNION_H
#define COOP_UNION_H

#include "../object.h"
#include "../macros.h"
#include "../functions/globals/__init__.h"
#include "Integer.h"

void __init_union(void);

DECLARE(Union, __init__, Object*, IntegerT num_types, ...);

DECLARE(Union, __contains__, bool, const Object *union_, const Object *T);

DECLARE(Union, __eq__, bool, const Object *a, const Object *b);

DECLARE(Union, __print__, void, const Object *obj);

DECLARE(Union, __len__, Object*, const Object *obj);

Object *new_union(IndexT num_types, ...);

bool union_contains(const Object *union_, const Object *T);

bool union_equals(const Object *a, const Object *b);

void union_print(const Object *obj);

#endif //COOP_UNION_H
