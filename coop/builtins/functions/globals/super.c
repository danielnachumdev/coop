//
// Created by danie on 25/07/2024.
//

#include "super.h"
#include "isinstance.h"
#include "../../types/Union.h"
#include "../../types/List.h"
#include "../../types/Array.h"

Object *super(const Object *self, IntegerT steps) {
    if (self == NULL) return NULL;
    if (steps <= 0) return NULL;
    if (steps == 1) return (Object *) self->type;
    Object *queue = implicitgetfunc(List, __init__)();
    implicitgetfunc(List, push)(queue, (Object *) self);
    Object *curT = NULL;
    for (IntegerT i = 0; i < steps; ++i) {
        curT = implicitgetfunc(List, poplast)(queue);
        if (isinstance(curT, Union)) {
            IntegerT length = *(IntegerT *) implicitgetfunc(Union, __len__)(curT)->data;
            for (IntegerT j = 0; j < length; ++j)
                implicitgetfunc(List, push)(queue, implicitgetfunc(Array, __getitem__)(curT->data, j));
        } else
            implicitgetfunc(List, push)(queue, (Object *) curT->type);
    }
    return implicitgetfunc(List, poplast)(queue);
}