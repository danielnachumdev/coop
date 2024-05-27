//
// Created by danie on 18/05/2024.
//

#ifndef COOP_OBJECT_H
#define COOP_OBJECT_H

#include "core/memory/allocator.h"

typedef struct Object {
    struct Object *type;
    unsigned int num_attributes;
    struct Object **attributes;
    void *data;
} Object;

#define new_object(amount) acquire(sizeof(Object)*amount).nullable
#define new_object_ptr(amount) acquire(sizeof(Object*)*amount).nullable
#endif //COOP_OBJECT_H
