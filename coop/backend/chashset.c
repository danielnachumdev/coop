//
// Created by danie on 29/05/2024.
//

#include <stdarg.h>
#include "chashset.h"
#include "../builtins/macros.h"


#define DEFAULT_START_LENGTH 8
#define DEFAULT_MINIMUM_LENGTH DEFAULT_START_LENGTH
#define DEFAULT_LOWER_BOUND 0.25
#define DEFAULT_UPPER_BOUND 0.75
#define DEFAULT_MULTIPLIER 2.0

const CHashSetStrategy default_chashset_strategy = (const CHashSetStrategy) {
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


bool default_chashset_pointer_comparer(const void *a, const void *b) {
    return a == b;
}

CHashSet *
chashset_new(DuplicatorT(data_dup), ConsumerT(data_free), ComparerT(data_comparer), const CHashSetStrategy *strategy,
             HashT(hash)) {
    if (data_dup == NULL || data_free == NULL || strategy == NULL || hash == NULL || data_comparer == NULL) return NULL;
    if (not(strategy->lower_bound < strategy->upper_bound || strategy->initial_length > 0)) return NULL;
    CHashSet *res = builtin_new(sizeof(CHashSet));
    if (res == NULL) return NULL;
    res->hash = hash;
    res->data_dup = data_dup;
    res->data_free = data_free;
    res->data_comparer = data_comparer;
    res->strategy = builtin_new(sizeof(CHashSetStrategy));
    if (res->strategy == NULL) {
        builtin_free(res);
        return NULL;
    }
    *(res->strategy) = *strategy;
    res->count = 0;
    res->length = res->strategy->initial_length;
    res->arr = builtin_new(sizeof(CLinkedList *) * res->length);
    if (res->arr == NULL) {
        builtin_free(res->strategy);
        builtin_free(res);
        return NULL;
    }
    for (int i = 0; i < res->length; ++i) {
        res->arr[i] = clinkedlist_new(res->data_dup, res->data_free, res->data_comparer);
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

void chashset_free(CHashSet **h) {
    if (h == NULL || *h == NULL) return;
    for (int i = 0; i < (*h)->length; ++i)
        clinkedlist_free((*h)->arr + i);
    builtin_free((*h)->strategy);
    builtin_free((*h)->arr);
    builtin_free(*h);
    *h = NULL;
}

bool chashset_contains(const CHashSet *h, const void *p) {
    if (h == NULL || p == NULL) return false;
    unsigned long index = h->hash(p) % h->length;
    return clinkedlist_contains(h->arr[index], p);
}

bool chashmap_resize(CHashSet *h) {
    if (h == NULL) return false;
    if (h->length * h->strategy->lower_bound <= h->count && h->count <= h->length * h->strategy->upper_bound)
        return true;
    if (h->count < h->strategy->minimum_length) return true;
    unsigned int new_length = cast(h->length * h->strategy->multiplier, unsigned int);
    if (h->length * h->strategy->lower_bound > h->count)
        new_length = cast(h->length / h->strategy->multiplier, unsigned int);
    CLinkedList **new_arr = builtin_new(sizeof(CLinkedList *) * new_length);
    if (new_arr == NULL) return false;
    for (int i = 0; i < new_length; ++i) {
        new_arr[i] = clinkedlist_new(h->data_dup, h->data_free, h->data_comparer);
        if (new_arr[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                builtin_free(new_arr[j]);
            }
            builtin_free(new_arr);
            return false;
        }
    }
    for (int i = 0; i < h->length; ++i) {
        CNode *cur = h->arr[i]->head;
        while (cur != NULL) {
            unsigned int index = h->hash(cur->data) % new_length;
            clinkedlist_add(new_arr[index], cur->data);
            cur = cur->next;
        }
        clinkedlist_free(&h->arr[i]);
    }
    builtin_free(h->arr);
    h->arr = new_arr;
    h->length = new_length;
    return true;
}

bool chashset_add_impl(CHashSet *h, void *p, ...) {
    if (h == NULL || p == NULL) return false;
    unsigned long index = h->hash(p) % h->length;
    if (clinkedlist_contains(h->arr[index], p)) return true;
    if (clinkedlist_add(h->arr[index], p) == NULL)
        return false;
    h->count += 1;
    return chashmap_resize(h);
}

void chashset_remove(CHashSet *h, void *p) {
    if (h == NULL || p == NULL) return;
    unsigned long index = h->hash(p) % h->length;
    clinkedlist_remove(h->arr[index], p);
    h->count -= 1;
    chashmap_resize(h);
}