//
// Created by danie on 28/05/2024.
//

#ifndef COOP_SETATTR_H
#define COOP_SETATTR_H

#include "../../object.h"

bool __append_attr(Object *obj, Object *attr);

void setattr(Object *obj, const char *key, Object *value);

#endif //COOP_SETATTR_H
