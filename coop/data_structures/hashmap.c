//
// Created by danie on 29/05/2024.
//

#include "hashmap.h"
#include "../globals/macros.h"
#include "../globals/__init__.h"


#define DEFAULT_COUNT 0
#define DEFAULT_LENGTH 2
#define DEFAULT_LOWER_BOUND 0.25
#define DEFAULT_UPPER_BOUND 0.75
#define DEFAULT_MULTIPLIER 2.0

const HashmapStrategy default_hashmap_strategy = (HashmapStrategy) {
        .lower_bound=DEFAULT_LOWER_BOUND,
        .upper_bound = DEFAULT_UPPER_BOUND,
        .multiplier = DEFAULT_MULTIPLIER
};

unsigned long default_hash(const void *p) {
    unsigned long int x = (unsigned long int) p;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return (unsigned long) x;
}

Hashmap *hashmap_new(void) {
    Hashmap *res = builtin_new(sizeof(Hashmap));
    if (res == NULL) return NULL;
    res->count = DEFAULT_COUNT;
    res->length = DEFAULT_LENGTH;
    res->arr = builtin_new(sizeof(LinkedList *) * DEFAULT_LENGTH);
    for (int i = 0; i < DEFAULT_LENGTH; ++i)
        res->arr[i] = linkedlist_new();
    res->hash = default_hash;
    res->strategy = acquire(sizeof(HashmapStrategy));
    *(res->strategy) = default_hashmap_strategy;
    return res;
}

void hashmap_free(Hashmap **h) {
    if (h == NULL) return;
    if (*h == NULL) return;
    for (int i = 0; i < (*h)->length; ++i)
        linkedlist_free((*h)->arr + i);
    builtin_free((*h)->arr);
    builtin_free(*h);
    *h = NULL;
}

bool hashmap_contains(const Hashmap *h, const void *p, bool(*comparer)(const void *p1, const void *p2)) {
    if (h == NULL || p == NULL) return false;
    unsigned long index = h->hash(p) % h->length;
    return linkedlist_contains(h->arr[index], p, comparer);
}

bool hashmap_resize(Hashmap *h) {
    if (h == NULL) return false;
    if (h->strategy->lower_bound * h->length < h->count && h->count < h->strategy->upper_bound * h->length) return true;
    unsigned int new_length = cast(h->length * h->strategy->multiplier, unsigned int); //RESIZE UP
    if (h->count <= h->strategy->lower_bound * h->length) {
        if (h->length == DEFAULT_LENGTH) return true;
        new_length = cast(h->length / h->strategy->multiplier, unsigned int); //RESIZE DOWN
    }
    LinkedList **new_arr = builtin_new(sizeof(LinkedList *) * new_length);
    if (new_arr == NULL) return false;
    for (unsigned int i = 0; i < new_length; ++i) {
        new_arr[i] = linkedlist_new();
        if (new_arr[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                LinkedList *ll = new_arr[i];
                linkedlist_free(&ll);
            }
            builtin_free(new_arr);
            return false;
        }
    }

    for (unsigned int i = 0; i < h->length; ++i) {
        LINKEDLIST_FOREACH(cur, h->arr[i], {
            void *p = cur->data;
            unsigned long index = h->hash(p) % new_length;
            linkedlist_add(new_arr[index], p);
        });
        linkedlist_free(h->arr + i);
    }
    builtin_free(h->arr);
    h->arr = new_arr;
    h->length = new_length;
    return true;
}

bool hashmap_insert(Hashmap *h, void *p) {
    if (h == NULL || p == NULL) return false;
    unsigned long index = h->hash(p) % h->length;
    if (linkedlist_add(h->arr[index], p) == NULL) return false;
    h->count += 1;
    return hashmap_resize(h);
}

void hashmap_remove(Hashmap *h, void *p) {
    if (h == NULL || p == NULL) return;
    unsigned long index = h->hash(p) % h->length;
    linkedlist_remove(h->arr[index], p);
    h->count -= 1;
    hashmap_resize(h);
}