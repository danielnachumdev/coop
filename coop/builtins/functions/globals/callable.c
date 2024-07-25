//
// Created by danie on 24/07/2024.
//

#include "callable.h"
#include "../attr/getattr.h"

bool callable(const Object *obj) {
    if (obj == NULL) return false;
    return getattr(obj, "__call__")->type == Function;
}