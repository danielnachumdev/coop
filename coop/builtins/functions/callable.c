//
// Created by danie on 24/07/2024.
//

#include "callable.h"
#include "attr/hasattr.h"

bool callable(const Object *obj) {
    if (obj == NULL) return false;
    return hasattr(obj, "__call__");
}