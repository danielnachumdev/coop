//
// Created by danie on 29/05/2024.
//

#ifndef COOP_HASHMAP_H
#define COOP_HASHMAP_H

#include <stdbool.h>
#include "linked_list.h"

typedef struct HashmapStrategy {
    double lower_bound;
    double upper_bound;
    double multiplier;
} HashmapStrategy;

extern const HashmapStrategy default_hashmap_strategy;

typedef struct Hashmap {
    unsigned long (*hash)(const void *p);

    HashmapStrategy *strategy;
    unsigned int count;
    unsigned int length;
    LinkedList **arr;
} Hashmap;


Hashmap *hashmap_new(void);

void hashmap_free(Hashmap **h);

bool hashmap_contains(const Hashmap *h, const void *p, bool(*comparer)(const void *p1, const void *p2));

bool hashmap_insert(Hashmap *h, void *p);

void hashmap_remove(Hashmap *h, void *p);

#endif //COOP_HASHMAP_H
