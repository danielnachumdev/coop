//
// Created by danie on 26/07/2024.
//

#ifndef COOP_SET_H
#define COOP_SET_H

#include "../object.h"
#include "../macros.h"

void __init_set(void);

DECLARE(Set, __init__, Object*, void);

DECLARE(Set, __len__, Object*, const Object *self);

DECLARE(Set, __contains__, bool, const Object *self, const Object *item);

DECLARE(Set, add, void, Object *self, Object *item);

DECLARE(Set, remove, void, Object *self, Object *item);

#endif //COOP_SET_H
