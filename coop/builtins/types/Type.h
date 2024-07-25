//
// Created by t-danachum on 27/05/2024.
//

#ifndef LOCAL_PLAYGROUND_TYPE_H
#define LOCAL_PLAYGROUND_TYPE_H

#include "../object.h"
#include "../macros.h"
#include "Integer.h"

void __init_type(void);

void type_print(const Object *obj);


void __init_type_functions(void);

DECLARE(Type, __init__, Object*, const char *name, IntegerT num_parents, Object parents[], IntegerT num_attributes, Attribute attrs[]);

DECLARE(Type, __print__, void, const Object *self);

DECLARE(Type, __eq__, bool, const Object *self, const Object *other);

#endif //LOCAL_PLAYGROUND_TYPE_H
