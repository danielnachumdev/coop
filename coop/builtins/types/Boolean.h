//
// Created by danie on 28/05/2024.
//

#ifndef COOP_BOOLEAN_H
#define COOP_BOOLEAN_H

#include "../../globals.h"

void __init_boolean(void);

Object *new_boolean(bool v);

bool boolean_equals(const Object *a, const Object *b);

#endif //COOP_BOOLEAN_H
