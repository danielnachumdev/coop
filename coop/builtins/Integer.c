//
// Created by t-danachum on 27/05/2024.
//

#include "Integer.h"
#include "../object.h"
#include "../memory/allocator.h"

Object *Integer = NULL;

void init_integer(void) {
    Integer = acquire(sizeof(Object));
    *Integer = init_object(Number);
}