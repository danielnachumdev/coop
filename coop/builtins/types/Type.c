//
// Created by t-danachum on 27/05/2024.
//

#include "Type.h"
#include "../../globals/object.h"
#include "../../memory/allocator.h"

Object *Type = NULL;

void __init_type(void) {
    Type = new_object(NULL, true);
    Type->type = Type;
}