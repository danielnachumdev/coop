//
// Created by danie on 28/05/2024.
//

#include "Array.h"

Object *Array = NULL;

void __init_array(void) {
    Array = new_object(Type);
}

Object *new_array(void) {
    Object *res = new_object(Array);
    if (res == NULL) return NULL;
    return res;
}