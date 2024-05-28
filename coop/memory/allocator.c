//
// Created by t-danachum on 21/05/2024.
//

#include <stddef.h>
#include "allocator.h"
#include "../macros.h"
#include "../data_structures/linked_list.h"

static Allocator *global_allocator = NULL;

void *default_acquire(unsigned long n) {
    void *p = builtin_new(n);
    if (p == NULL) return NULL;
    linkedlist_add(get_allocator()->structure, p);
    return p;
}

void default_release(void *p) {
    if (p == NULL) return;
    linkedlist_remove(get_allocator()->structure, p);
}

void default_clear(void) {
    LinkedList *ll = get_allocator()->structure;
    linkedlist_free(&ll);
    builtin_free(global_allocator);
}

Allocator *init_allocator(void) {
    Allocator *res = builtin_new(sizeof(Allocator));
    if (res == NULL) return NULL;
    res->structure = linkedlist_new();
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