//
// Created by t-danachum on 27/05/2024.
//

#include "Number.h"
#include "../../object.h"
#include "../../memory/allocator.h"

Object *Number = NULL;

void init_number(void) {
    Number = acquire(sizeof(Object));
    *Number = init_object(Type);
}