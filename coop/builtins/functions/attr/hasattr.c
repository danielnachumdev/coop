//
// Created by danie on 28/05/2024.
//

#include "hasattr.h"
#include "getattr.h"

bool hasattr(const Object *obj, const char *name) {
    return getattr(obj, name, NULL) != NULL;
}
