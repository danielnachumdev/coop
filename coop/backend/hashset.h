//
// Created by danie on 29/05/2024.
//

#ifndef COOP_HASHSET_H
#define COOP_HASHSET_H

#include <stdbool.h>
#include "linked_list.h"

#define HashT(name) __FUNCTION_POINTER_BUILDER(name,unsigned long,const void *p)

typedef struct HashSetStrategy {
    double lower_bound;
    double upper_bound;
    double multiplier;
    unsigned int initial_length;
    unsigned int minimum_length;
} HashSetStrategy;

extern const HashSetStrategy default_hashset_strategy;

typedef struct HashSet {
    HashT(hash);

    DuplicatorT(data_dup);

    ConsumerT(data_free);

    ComparerT(data_comparer);

    HashSetStrategy *strategy;
    unsigned int count;
    unsigned int length;
    LinkedList **arr;
} HashSet;

bool default_hashset_pointer_comparer(const void *a, const void *b);

HashSet *
hashset_new(DuplicatorT(data_dup), ConsumerT(data_free), ComparerT(data_comparer), const HashSetStrategy *strategy,
            HashT(hash));

unsigned long pointer_hash(const void *p);

void hashset_free(HashSet **h);

bool hashset_contains(const HashSet *h, const void *p);

bool hashset_add_impl(HashSet *h, void *p, ...);

#define hashset_add(h, p, ...) hashset_add_impl(h,p,## __VA_ARGS__,false)

void hashset_remove(HashSet *h, void *p);

#endif //COOP_HASHSET_H
