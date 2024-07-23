//
// Created by danie on 24/07/2024.
//

#include "iscallable.h"
#include "attr/getattr.h"

bool iscallable(const Object *obj) {
    if (obj == NULL) return false;
    Object *attr = getattr(obj, "__call__");
    if (attr == NULL) return false;
    return attr->type == Function;
}