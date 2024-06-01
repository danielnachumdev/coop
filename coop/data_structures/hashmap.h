//
// Created by danie on 29/05/2024.
//

#ifndef COOP_HASHMAP_H
#define COOP_HASHMAP_H

#include <stdbool.h>
#include "linked_list.h"

#define HashT(name) __FUNCTION_POINTER_BUILDER(name,unsigned long,const void *p)

typedef struct HashmapStrategy {
    double lower_bound;
    double upper_bound;
    double multiplier;
    unsigned int start_count;
    unsigned int start_length;
} HashmapStrategy;

extern const HashmapStrategy default_hashmap_strategy;

typedef struct Hashmap {
    HashT(hash);

    HashmapStrategy *strategy;
    unsigned int count;
    unsigned int length;
    LinkedList **arr;

    Duplicator(data_dup);

    Consumer(data_free);
} Hashmap;


Hashmap *hashmap_new(Duplicator(data_dup), Consumer(data_free), const HashmapStrategy *strategy, HashT(hash));

unsigned long default_hash(const void *p);

void hashmap_free(Hashmap **h);

bool hashmap_contains(const Hashmap *h, const void *p, bool(*comparer)(const void *p1, const void *p2));

bool hashmap_insert(Hashmap *h, void *p);

void hashmap_remove(Hashmap *h, void *p);

#endif //COOP_HASHMAP_H
