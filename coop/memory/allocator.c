//
// Created by t-danachum on 21/05/2024.
//

#include <stddef.h>
#include "allocator.h"
#include "../globals/macros.h"
#include "../data_structures/hashmap.h"

unsigned long int allocated_bytes = 0;
unsigned long int freed_bytes = 0;
static Allocator *global_allocator = NULL;

void *default_acquire(unsigned long n) {
    void *p = builtin_new(n);
    if (p == NULL) return NULL;
    hashmap_insert(get_allocator()->structure, p);
    allocated_bytes += n;
    return p;
}

void default_release(void *p, unsigned int size_in_bytes) {
    if (p == NULL) return;
    hashmap_remove(get_allocator()->structure, p);
    freed_bytes += size_in_bytes;
}

void default_clear(void) {
    Hashmap *h = get_allocator()->structure;
    hashmap_free(&h);
    builtin_free(global_allocator);
}

Allocator *init_allocator(void) {
    Allocator *res = builtin_new(sizeof(Allocator));
    if (res == NULL) return NULL;
    res->structure = hashmap_new();
    if (res->structure == NULL) {
        builtin_free(res);
        return NULL;
    }
    res->acquire = default_acquire;
    res->release = default_release;
    res->clear = default_clear;
    return res;
}

Allocator *get_allocator(void) {
    if (global_allocator != NULL) return global_allocator;
    global_allocator = init_allocator();
    return global_allocator;
}