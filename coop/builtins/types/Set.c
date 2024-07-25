//
// Created by danie on 26/07/2024.
//

#include "Set.h"
#include "Function.h"

Object *Set = NULL;

void __init_set(void) {
    Set = new_object(Type);
    explicitsetfunc(Set, __init__);
    explicitsetfunc(Set, __len__);
    explicitsetfunc(Set, __contains__);
    explicitsetfunc(Set, add);
    explicitsetfunc(Set, remove);
}

DEF(Set, __init__, Object *, {}, void)

DEF(Set, __len__, Object *, {}, const Object *self)

DEF(Set, __contains__, bool, {}, const Object *self, const Object *item)

DEF(Set, add, void, {}, Object *self, Object *item)

DEF(Set, remove, void, {}, Object *self, Object *item)