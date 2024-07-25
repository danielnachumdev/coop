//
// Created by danie on 26/07/2024.
//

#include "contains.h"

bool contains(const Object *obj, const Object *item) {
    if (obj == NULL || item == NULL) return NULL;
    return cast(getattr(obj, "__contains__")->data, bool(*)(const Object*, const Object*))(obj, item);
}