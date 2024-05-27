//
// Created by t-danachum on 27/05/2024.
//

#include "Type.h"
#include "../object.h"
#include "../memory/allocator.h"

Object *Type = NULL;

void init_type(void) {
    Type = acquire(sizeof(Object));
    *Type = init_object(Type);
}