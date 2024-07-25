//
// Created by danie on 25/07/2024.
//

#ifndef COOP_LIST_H
#define COOP_LIST_H

#include "../object.h"
#include "../functions/globals/__init__.h"
#include "../macros.h"

void __init_list(void);

DECLARE(List, __init__, Object *, void);

DECLARE(List, push, void, Object *self, Object *obj);

DECLARE(List, popfirst, Object *, Object *self);

DECLARE(List, poplast, Object *, Object *self);

DECLARE(List, append, void, Object *self, Object *obj);

DECLARE(List, isempty, bool, Object *self);

DECLARE(List, __bool__, bool, Object *self);

#endif //COOP_LIST_H
