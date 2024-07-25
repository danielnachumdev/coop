//
// Created by danie on 02/06/2024.
//

#include "isinstance.h"
#include "../../__init__.h"

bool isinstance(const Object *obj, const Object *T) {
    if (obj == NULL || T == NULL) return false;
    if (T->type == Union) {
        IntegerT length = *(IntegerT *) explicitgetfunc(Array, __len__)(T->data)->data;
        Array__getitem___prototype get = Array__getitem__;
        for (IntegerT i = 0; i < length; ++i)
            if (isinstance(obj, get(T->data, i))) return true;
    } else {
        const Object *cur_type = obj->type;
        if (obj->type == NULL) return false;
        while (cur_type != Type) {
            if (cur_type == T) return true;
            cur_type = cur_type->type;
        }
        if (cur_type == Type && T == Type) return true;
    }
    return false;
}
