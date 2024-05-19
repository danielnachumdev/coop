//
// Created by danie on 19/05/2024.
//

#ifndef COOP_HASHMAP_H
#define COOP_HASHMAP_H

#include "linked_list.h"

typedef struct Hashmap {
    LinkedList **arr;
    unsigned int size;
} Hashmap;

Hashmap * hashmap_new();

extern IRandomAccess random_access_hash_map;
#endif //COOP_HASHMAP_H
