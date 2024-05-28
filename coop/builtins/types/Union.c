//
// Created by danie on 28/05/2024.
//

#include <stdarg.h>
#include "Union.h"
#include "../../globals.h"

Object *Union = NULL;

void __init_union(void) {
    Union = new_object(Type);
}

Object *new_union(unsigned long int num_types, ...) {
    Object *res = new_object(Union);
    if (res == NULL) return NULL;

    res->data = new_array(num_types, Type);

    va_list valist;
    va_start(valist, num_types);
    for (unsigned int i = 0; i < num_types; ++i) {
        const Object *cur = va_arg(valist, const Object*);
        if (not(isinstance(cur, Type))) return NULL;
    }
    va_end(valist);
    return res;
}