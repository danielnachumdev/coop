//
// Created by danie on 16/05/2024.
//

#ifndef MACROPYTHON_ALLOCATOR_H
#define MACROPYTHON_ALLOCATOR_H

#include <stddef.h>
#include "../data_structures//linked_list.h"
#include "../data_structures/interface_random_access.h"
#include "../optional.h"

typedef struct Allocator {
    IRandomAccess *structure;

    Optional (*new)(long unsigned int size);

    void (*free)(void *p);

    void (*clean)(void);
} Allocator;

Allocator *get_allocator(void);

#define acquire(size) get_allocator()->new(size)
#define release(p) get_allocator()->free(p)

#endif //MACROPYTHON_ALLOCATOR_H
