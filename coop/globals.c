//
// Created by danie on 28/05/2024.
//
#include "globals.h"

bool isinstance(const Object *obj, const Object *T) {
    return obj->type == T;
}