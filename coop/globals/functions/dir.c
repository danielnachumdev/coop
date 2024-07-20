
//
// Created by danie on 02/06/2024.
//

#include "dir.h"
#include "../../builtins/types/__init__.h"
#include "../constants.h"
#include "../../builtins/functions/attr/getattr.h"
#include "../../builtins/functions/print.h"

void dir(const Object *obj) {
    if (obj == NULL) return;
    println(getattr(obj->type, NAME));
}