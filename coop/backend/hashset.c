//
// Created by danie on 29/05/2024.
//

#include <stdarg.h>
#include "hashset.h"
#include "../builtins/macros.h"


#define DEFAULT_START_LENGTH 8
#define DEFAULT_MINIMUM_LENGTH DEFAULT_START_LENGTH
#define DEFAULT_LOWER_BOUND 0.25
#define DEFAULT_UPPER_BOUND 0.75
#define DEFAULT_MULTIPLIER 2.0

const HashSetStrategy default_hashset_strategy = (const HashSetStrategy) {
        .lower_bound=DEFAULT_LOWER_BOUND,
        .upper_bound = DEFAULT_UPPER_BOUND,
        .multiplier = DEFAULT_MULTIPLIER,
        .initial_length=DEFAULT_START_LENGTH,
        .minimum_length=DEFAULT_MINIMUM_LENGTH
};

unsigned long pointer_hash(const void *p) {
    unsigned long int x = (unsigned long int) p;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return (unsigned long) x;
}


bool default_hashset_pointer_comparer(const void *a, const void *b) {
    return a == b;
}

HashSet *
hashset_new(DuplicatorT(data_dup), ConsumerT(data_free), ComparerT(data_comparer), const HashSetStrategy *strategy,
            HashT(hash)) {
    if (data_dup == NULL || data_free == NULL || strategy == NULL || hash == NULL || data_comparer == NULL) return NULL;
    if (not(strategy->lower_bound < strategy->upper_bound || strategy->initial_length > 0)) return NULL;
    HashSet *res = builtin_new(sizeof(HashSet));
    if (res == NULL) return NULL;
    res->hash = hash;
    res->data_dup = data_dup;
    res->data_free = data_free;
    res->data_comparer = data_comparer;
    res->strategy = builtin_new(sizeof(HashSetStrategy));
    if (res->strategy == NULL) {
        builtin_free(res);
        return NULL;
    }
    *(res->strategy) = *strategy;
    res->count = 0;
    res->length = res->strategy->initial_length;
    res->arr = builtin_new(sizeof(LinkedList *) * res->length);
    if (res->arr == NULL) {
        builtin_free(res->strategy);
        builtin_free(res);
        return NULL;
    }
    for (int i = 0; i < res->length; ++i) {
        res->arr[i] = linkedlist_new(res->data_dup, res->data_free, res->data_comparer);
        if (res->arr[i] == NULL) {
            for (int j = 0; j < i; ++j)
                builtin_free(res->arr[i]);
            builtin_free(res->strategy);
            builtin_free(res->arr);
            builtin_free(res);
            return NULL;
        }
    }
    return res;
}

void hashset_free(HashSet **h) {
    if (h == NULL || *h == NULL) return;
    for (int i = 0; i < (*h)->length; ++i)
        linkedlist_free((*h)->arr + i);
    builtin_free((*h)->strategy);
    builtin_free((*h)->arr);
    builtin_free(*h);
    *h = NULL;
}

bool hashset_contains(const HashSet *h, const void *p) {
    if (h == NULL || p == NULL) return false;
    unsigned long index = h->hash(p) % h->length;
    return linkedlist_contains(h->arr[index], p);
}

bool hashmap_resize(HashSet *h) {
    if (h == NULL) return false;
    if (h->length * h->strategy->lower_bound <= h->count && h->count <= h->length * h->strategy->upper_bound)
        return true;
    if (h->count < h->strategy->minimum_length) return true;
    unsigned int new_length = cast(h->length * h->strategy->multiplier, unsigned int);
    if (h->length * h->strategy->lower_bound > h->count)
        new_length = cast(h->length / h->strategy->multiplier, unsigned int);
    LinkedList **new_arr = builtin_new(sizeof(LinkedList *) * new_length);
    if (new_arr == NULL) return false;
    for (int i = 0; i < new_length; ++i) {
        new_arr[i] = linkedlist_new(h->data_dup, h->data_free, h->data_comparer);
        if (new_arr[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                builtin_free(new_arr[j]);
            }
            builtin_free(new_arr);
            return false;
        }
    }
    for (int i = 0; i < h->length; ++i) {
        Node *cur = h->arr[i]->head;
        while (cur != NULL) {
            unsigned int index = h->hash(cur->data) % new_length;
            linkedlist_add(new_arr[index], cur->data);
            cur = cur->next;
        }
        linkedlist_free(&h->arr[i]);
    }
    builtin_free(h->arr);
    h->arr = new_arr;
    h->length = new_length;
    return true;
}

bool hashset_add_impl(HashSet *h, void *p, ...) {
    if (h == NULL || p == NULL) return false;
    unsigned long index = h->hash(p) % h->length;
    if (linkedlist_contains(h->arr[index], p)) return true;
    if (linkedlist_add(h->arr[index], p) == NULL)
        return false;
    h->count += 1;
    return hashmap_resize(h);
}

void hashset_remove(HashSet *h, void *p) {
    if (h == NULL || p == NULL) return;
    unsigned long index = h->hash(p) % h->length;
    linkedlist_remove(h->arr[index], p);
    h->count -= 1;
    hashmap_resize(h);
}