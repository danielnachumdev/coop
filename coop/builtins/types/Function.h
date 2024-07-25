//
// Created by t-danachum on 27/05/2024.
//

#ifndef LOCAL_PLAYGROUND_FUNCTION_H
#define LOCAL_PLAYGROUND_FUNCTION_H

#include "../object.h"
#include "../macros.h"

void __init_function(void);

Object *__new_function(const char *name, void *(*impl)(), Object *return_type, Object *arguments_array);

DECLARE(Function, __init__, Object *, const char *name, void *(*impl)(), Object *return_type, Object *arguments_array);

DECLARE(Function, __print__, void, const Object*);

DECLARE(Function, __eq__, bool, const Object *, const Object *);

#endif //LOCAL_PLAYGROUND_FUNCTION_H
