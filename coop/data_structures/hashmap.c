//
// Created by danie on 29/05/2024.
//

#include "hashmap.h"
#include "../globals/macros.h"
#include "../globals/__init__.h"


#define DEFAULT_START_COUNT 0
#define DEFAULT_START_LENGTH 2
#define DEFAULT_LOWER_BOUND 0.25
#define DEFAULT_UPPER_BOUND 0.75
#define DEFAULT_MULTIPLIER 2.0

const HashmapStrategy default_hashmap_strategy = (HashmapStrategy) {
        .lower_bound=DEFAULT_LOWER_BOUND,
        .upper_bound = DEFAULT_UPPER_BOUND,
        .multiplier = DEFAULT_MULTIPLIER,
        .start_count=DEFAULT_START_COUNT,
        .start_length=DEFAULT_START_LENGTH
};

unsigned long default_hash(const void *p) {
    unsigned long int x = (unsigned long int) p;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return (unsigned long) x;
}

bool default_hashmap_pointer_comparer(const void *a, const void *b) {
    return a == b;
}

Hashmap *
hashmap_new(DuplicatorT(data_dup), ConsumerT(data_free), ComparerT(data_comparer), const HashmapStrategy *strategy,
            HashT(hash)) {
    if (data_dup == NULL || data_free == NULL || strategy == NULL || hash == NULL || data_comparer == NULL) return NULL;
    Hashmap *res = builtin_new(sizeof(Hashmap));
    if (res == NULL) return NULL;
    res->hash = hash;
    res->data_dup = data_dup;
    res->data_free = data_free;
    res->data_comparer = data_comparer;
    res->strategy = builtin_new(sizeof(HashmapStrategy));
    if (res->strategy == NULL) {
        builtin_free(res);
        return NULL;
    }
    *(res->strategy) = *strategy;
    res->count = res->strategy->start_count;
    res->length = res->strategy->start_length;
    res->arr = builtin_new(sizeof(LinkedList *) * res->length);
    if (res->arr == NULL) {
        builtin_free(res->strategy);
        builtin_free(res);
        return NULL;
    }
    for (int i = 0; i < DEFAULT_START_LENGTH; ++i) {
        res->arr[i] = linkedlist_new(res->data_dup, res->data_free, res->data_comparer);
        if (res->arr[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                builtin_free(res->arr[i]);
            }
            builtin_free(res->strategy);
            builtin_free(res);
            return NULL;
        }
    }
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

bool hashmap_contains(const Hashmap *h, const void *p) {
    if (h == NULL || p == NULL) return false;
    unsigned long index = h->hash(p) % h->length;
    return linkedlist_contains(h->arr[index], p);
}

bool hashmap_resize(Hashmap *h) {
    if (h == NULL) return false;
    if (h->strategy->lower_bound * h->length < h->count && h->count < h->strategy->upper_bound * h->length) return true;
    unsigned int new_length = cast(h->length * h->strategy->multiplier, unsigned int); //RESIZE UP
    if (h->count <= h->strategy->lower_bound * h->length) {
        if (h->length == DEFAULT_START_LENGTH) return true;
        new_length = cast(h->length / h->strategy->multiplier, unsigned int); //RESIZE DOWN
    }
    LinkedList **new_arr = builtin_new(sizeof(LinkedList *) * new_length);
    if (new_arr == NULL) return false;
    for (unsigned int i = 0; i < new_length; ++i) {
        new_arr[i] = linkedlist_new(h->data_dup, h->data_free, h->data_comparer);
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