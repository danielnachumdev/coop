//
// Created by danie on 27/07/2024.
//

#include "hash.h"
#include "../attr/getattr.h"

Object *hash(const Object *obj) {
    if (obj == NULL) return NULL;
    return cast(getattr(obj, "__hash__")->data, Object*(*)(const Object*))(obj);
}