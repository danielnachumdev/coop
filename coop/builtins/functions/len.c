//
// Created by danie on 24/07/2024.
//

#include "len.h"
#include "attr/getattr.h"

IndexT len(const Object *obj) {
//    TODO: should raise an exception when early termination
    if (obj == NULL) return 0;
    Object *attr = getattr(obj, "__len__");
    if (attr == NULL) return 0;
    if (attr->type != Integer) return 0;
    return *cast(attr->data, IndexT*);
}