//
// Created by danie on 19/05/2024.
//

#ifndef COOP_HASHMAP_H
#define COOP_HASHMAP_H

#include "linked_list.h"

typedef LinkedList *Bucket;
typedef struct Hashmap {
    Bucket *buckets;
    unsigned int num_buckets;
    unsigned int count;
    unsigned int change_factor;
    double scale_down_threshold;
    double scale_up_threshold;

    long unsigned int (*hash)(long unsigned int);
} Hashmap;

Hashmap *hashmap_new();

void hashmap_free(Hashmap **);

Node *hashmap_get(Hashmap *, void *);

Node *hashmap_del(Hashmap *, void *);

Node *hashmap_add(Hashmap *ll, void *p);

#endif //COOP_HASHMAP_H
