//
// Created by t-danachum on 27/05/2024.
//

#include "Function.h"
#include "../object.h"
#include "../memory/allocator.h"

Object *Function = NULL;

void init_function(void) {
    Function = acquire(sizeof(Object));
    *Function = init_object(Number);
}