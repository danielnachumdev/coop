//
// Created by danie on 25/07/2024.
//

#include "super.h"
#include "isinstance.h"
#include "../types/Union.h"
#include "../types/List.h"
#include "../types/Array.h"

Object *super(const Object *self, IntegerT steps) {
    if (self == NULL) return NULL;
    if (steps <= 0) return NULL;
    if (steps == 1) return (Object *) self->type;
    Object *queue = explicitgetfunc(List, __init__)();
    explicitgetfunc(List, push)(queue, (Object *) self);
    Object *curT = NULL;
    for (IntegerT i = 0; i < steps; ++i) {
        curT = explicitgetfunc(List, poplast)(queue);
        if (isinstance(curT, Union)) {
            IntegerT length = *(IntegerT *) explicitgetfunc(Union, __len__)(curT)->data;
            for (IntegerT j = 0; j < length; ++j)
                explicitgetfunc(List, push)(queue, explicitgetfunc(Array, __getitem__)(curT->data, j));
        } else
            explicitgetfunc(List, push)(queue, (Object *) curT->type);
    }
    return explicitgetfunc(List, poplast)(queue);
}