
//
// Created by danie on 02/06/2024.
//

#include "dir.h"
#include "../constants.h"
#include "attr/getattr.h"
#include "print.h"

void dir(const Object *obj) {
    if (obj == NULL) return;
    println(getattr(obj->type, NAME));
}