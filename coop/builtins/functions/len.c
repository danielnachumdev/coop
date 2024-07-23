//
// Created by danie on 24/07/2024.
//

#include "len.h"
#include "attr/getattr.h"

long long len(const Object *obj) {
    if (obj == NULL) return 0;
    Object *attr = getattr(obj, "__len__");
    if (attr == NULL) return 0;
    return cast(attr->data, long long);
}