//
// Created by t-danachum on 27/05/2024.
//

#include "Field.h"
#include "../object.h"
#include "../memory/allocator.h"

Object *Field = NULL;

void init_field(void) {
    Field = acquire(sizeof(Object));
    *Field = init_object(Type);
}