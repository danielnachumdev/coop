//
// Created by danie on 02/06/2024.
//

#include "isinstance.h"
#include "../__init__.h"
#include "../constants.h"

bool isinstance(const Object *obj, const Object *T) {
    if (obj == NULL || T == NULL) return false;
    if (T->type == Union) {
//        TODO
    } else {
        const Object *cur_type = obj->type;
        while (cur_type != Type) {
            if (cur_type == T) return true;
            cur_type = cur_type->type;
        }
        if (cur_type == Type && T == Type) return true;
    }
    return false;
}
