//
// Created by t-danachum on 27/05/2024.
//

#ifndef LOCAL_PLAYGROUND_FUNCTION_H
#define LOCAL_PLAYGROUND_FUNCTION_H

#include "../../object.h"

void __init_function(void);

Object *new_function(const char *name, void *(*impl)());

#endif //LOCAL_PLAYGROUND_FUNCTION_H
