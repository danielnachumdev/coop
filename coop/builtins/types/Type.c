//
// Created by t-danachum on 27/05/2024.
//

#include <stdio.h>
#include "Type.h"
#include "../object.h"
#include "../../memory/allocator.h"
#include "../functions/print.h"
#include "../functions/attr/getattr.h"


Object *Type = NULL;

void __init_type(void) {
    Type = new_object(NULL);
    Type->type = Type;
}

void type_print(const Object *obj) {
    if (obj == NULL)return;
    printf("Type(name=");
    __print_object(getattr(obj, "__name__"));
    printf(")");
}