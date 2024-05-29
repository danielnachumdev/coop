//
// Created by danie on 29/05/2024.
//

#include "hashmap.h"
#include "../macros.h"


#define DEFAULT_COUNT 0
#define DEFAULT_LENGTH 4

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

bool hashmap_insert(Hashmap *h, void *p) {
    if (h == NULL || p == NULL) return false;
    unsigned long index = h->hash(p) % h->length;
    return linkedlist_add(h->arr[index], p) != NULL;
}

void hashmap_remove(Hashmap *h, void *p) {
    if (h == NULL || p == NULL) return;
    unsigned long index = h->hash(p) % h->length;
    linkedlist_remove(h->arr[index], p);
}