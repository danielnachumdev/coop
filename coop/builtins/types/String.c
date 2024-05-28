//
// Created by t-danachum on 27/05/2024.
//

#include "String.h"
#include "../../object.h"
#include "../../memory/allocator.h"

Object *String = NULL;

void init_string(void) {
    String = acquire(sizeof(Object));
    *String = init_object(Type);
}