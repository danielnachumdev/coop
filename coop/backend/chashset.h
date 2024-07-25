//
// Created by danie on 29/05/2024.
//

#ifndef COOP_CHASHSET_H
#define COOP_CHASHSET_H

#include <stdbool.h>
#include "clinked_list.h"

#define HashT(name) __FUNCTION_POINTER_BUILDER(name,unsigned long,const void *p)

typedef struct CHashSetStrategy {
    double lower_bound;
    double upper_bound;
    double multiplier;
    unsigned int initial_length;
    unsigned int minimum_length;
} CHashSetStrategy;

extern const CHashSetStrategy default_chashset_strategy;

typedef struct CHashSet {
    HashT(hash);

    DuplicatorT(data_dup);

    ConsumerT(data_free);

    ComparerT(data_comparer);

    CHashSetStrategy *strategy;
    unsigned int count;
    unsigned int length;
    CLinkedList **arr;
} CHashSet;

bool default_chashset_pointer_comparer(const void *a, const void *b);

CHashSet *
chashset_new(DuplicatorT(data_dup), ConsumerT(data_free), ComparerT(data_comparer), const CHashSetStrategy *strategy,
             HashT(hash));

unsigned long pointer_hash(const void *p);

void chashset_free(CHashSet **h);

bool chashset_contains(const CHashSet *h, const void *p);

bool chashset_add_impl(CHashSet *h, void *p, ...);

#define chashset_add(h, p, ...) chashset_add_impl(h,p,## __VA_ARGS__,false)

void chashset_remove(CHashSet *h, void *p);

#endif //COOP_CHASHSET_H
