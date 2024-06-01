//
// Created by t-danachum on 27/05/2024.
//

#ifndef LOCAL_PLAYGROUND_INTEGER_H
#define LOCAL_PLAYGROUND_INTEGER_H

#include "../../globals/object.h"

void __init_integer(void);

Object *new_integer(long long int n);

bool integer_equals(const Object *a, const Object *b);

#endif //LOCAL_PLAYGROUND_INTEGER_H
