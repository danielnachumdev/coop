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
    Object *queue = igetfunc(List, __init__)();
    igetfunc(List, push)(queue, (Object *) self);
    Object *curT = NULL;
    for (IntegerT i = 0; i < steps; ++i) {
        curT = igetfunc(List, poplast)(queue);
        if (isinstance(curT, Union)) {
            IntegerT length = *(IntegerT *) igetfunc(Union, __len__)(curT)->data;
            for (IntegerT j = 0; j < length; ++j)
                igetfunc(List, push)(queue, igetfunc(Array, __getitem__)(curT->data, j));
        } else
            igetfunc(List, push)(queue, (Object *) curT->type);
    }
    return igetfunc(List, poplast)(queue);
}