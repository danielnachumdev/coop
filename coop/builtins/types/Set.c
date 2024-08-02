//
// Created by danie on 26/07/2024.
//

#include "Set.h"
#include "Function.h"
#include "String.h"

Object *Set = NULL;

void __init_set(void) {
    Set = new_object(Type);
    setattr(Set, "__name__", igetfunc(String, __init__)("Set"));
    isetfunc(Set, __init__);
    isetfunc(Set, __len__);
    isetfunc(Set, __contains__);
    isetfunc(Set, add);
    isetfunc(Set, remove);
}

DEF(Set, __init__, Object *, {}, void)

DEF(Set, __len__, Object *, {}, const Object *self)

DEF(Set, __contains__, bool, {}, const Object *self, const Object *item)

DEF(Set, add, void, {}, Object *self, Object *item)

DEF(Set, remove, void, {}, Object *self, Object *item)