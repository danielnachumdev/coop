//
// Created by t-danachum on 27/05/2024.
//

#ifndef LOCAL_PLAYGROUND_FUNCTION_H
#define LOCAL_PLAYGROUND_FUNCTION_H

#include "../object.h"
#include "../macros.h"

void __init_function(void);

bool function_equals(const Object *a, const Object *b);

Object *new_function(const char *name, void *(*impl)(), Object *return_type, Object *arguments_array);

Object *new_runnable(const char *name, void (*impl)(void));

DECLARE(Function, __print__, void, const Object*);

#endif //LOCAL_PLAYGROUND_FUNCTION_H
