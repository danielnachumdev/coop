//
// Created by t-danachum on 21/05/2024.
//

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include "allocator.h"
#include "../globals/macros.h"
#include "../data_structures/hashset.h"

unsigned long int allocated_bytes = 0;
unsigned long int freed_bytes = 0;
static Allocator *global_allocator = NULL;

void *default_acquire(unsigned long n, ...) {
    VA_ARGS_LIST_1_ARG(keep_allocated_address_constant, bool);
    void *p = builtin_new(n);
    if (p == NULL) return NULL;
    hashset_add(get_allocator()->structure, p, keep_allocated_address_constant);
    allocated_bytes += n;
    return p;
}

void default_release(void *p) {
    if (p == NULL) return;
    hashset_remove(get_allocator()->structure, p);
}

void default_clear(void) {
    HashSet *h = get_allocator()->structure;
    hashset_free(&h);
    builtin_free(global_allocator);
}

void naive_free__(void *p) {
    builtin_free(p);
}

void *naive_dup__(const void *p) {
    return (void *) p;
}

Allocator *init_allocator(void) {
    Allocator *res = builtin_new(sizeof(Allocator));
    if (res == NULL) return NULL;
    res->structure = hashset_new(naive_dup__, naive_free__, default_hashset_pointer_comparer, &default_hashset_strategy,
                                 default_hashset_hash);
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