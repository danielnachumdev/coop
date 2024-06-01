//
// Created by danie on 28/05/2024.
//

#ifndef COOP_UNION_H
#define COOP_UNION_H

#include "../../globals/object.h"

void __init_union(void);

Object *new_union(unsigned long int num_types, ...);

bool union_contains(const Object *uni, const Object *T);

bool union_equals(const Object *a, const Object *b);

#endif //COOP_UNION_H
