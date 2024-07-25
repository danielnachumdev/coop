//
// Created by t-danachum on 27/05/2024.
//

#ifndef LOCAL_PLAYGROUND_INTEGER_H
#define LOCAL_PLAYGROUND_INTEGER_H

#include "../object.h"
#include "../macros.h"

typedef long long int IntegerT;

void __init_integer(void);

void __init_integer_functions(void);

Object *__new_integer(IntegerT n);

DECLARE(Integer, __init__, Object*, IntegerT);

DECLARE(Integer, __eq__, bool, const Object *self, const Object *other);

DECLARE(Integer, __print__, void, const Object *self);

#endif //LOCAL_PLAYGROUND_INTEGER_H
