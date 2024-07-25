//
// Created by t-danachum on 27/05/2024.
//

#ifndef LOCAL_PLAYGROUND_STRING_H
#define LOCAL_PLAYGROUND_STRING_H

#include "../object.h"
#include "../macros.h"

void __init_string(void);

void __init_string_functions(void);

Object *__new_string(const char *s);

DECLARE(String, __init__, Object*, const char *);

DECLARE(String, __eq__, bool, const Object*, const Object*);

DECLARE(String, __print__, void, const Object*);

DECLARE(String, __bool__, bool, const Object *self);

#endif //LOCAL_PLAYGROUND_STRING_H
