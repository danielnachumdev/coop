//
// Created by t-danachum on 21/05/2024.
//

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "allocator.h"
#include "../builtins/macros.h"
#include "../backend/hashset.h"

unsigned long int allocated_bytes = 0;
unsigned long int freed_bytes = 0;
Allocator *__coop_allocator__ = NULL;
Allocator *__user_allocator__ = NULL;
Allocator *__global_allocator__ = NULL;

void *default_acquire(unsigned long n) {
    void *p = builtin_new(n);
    if (p == NULL) return NULL;

    Allocator *a = get_allocator();
    a->__impl_acquire(a->structure, p);
    allocated_bytes += n;
    return p;
}

void default_release(void *p) {
    if (p == NULL) return;
    get_allocator()->__impl_release(get_allocator()->structure, p);
}

void default_clear(Allocator *allocator) {
    if (allocator == NULL) return;
    allocator->__impl_clear(&allocator->structure);
    builtin_free(allocator);
}

void naive_free__(void *p) {
    builtin_free(p);
}

void *naive_dup__(const void *p) {
    return (void *) p;
}

Allocator *allocator_new_hashset(void) {
    Allocator *res = builtin_new(sizeof(Allocator));
    if (res == NULL) return NULL;
    res->allocator_type = AllocatorHashSet;
    res->structure = hashset_new(naive_dup__, naive_free__, default_hashset_pointer_comparer, &default_hashset_strategy,
                                 pointer_hash);
    if (res->structure == NULL) {
        builtin_free(res);
        return NULL;
    }
    res->__impl_acquire = cast(hashset_add_impl, void *(*)(void *, void *));
    res->__impl_release = cast(hashset_remove, bool(*)(void*, void*));
    res->__impl_clear = cast(hashset_free, void(*)(void**));
    res->acquire = default_acquire;
    res->release = default_release;
    res->clear = default_clear;
    return res;
}

Allocator *allocator_new_linkedlist(void) {
    Allocator *res = builtin_new(sizeof(Allocator));
    if (res == NULL) return NULL;
    res->structure = linkedlist_new(naive_dup__, naive_free__, default_hashset_pointer_comparer);
    res->allocator_type = AllocatorLinkedList;
    if (res->structure == NULL) {
        builtin_free(res);
        return NULL;
    }
    res->__impl_acquire = cast(linkedlist_add, void *(*)(void *, void *));
    res->__impl_release = cast(linkedlist_remove, bool(*)(void*, void*));
    res->__impl_clear = cast(linkedlist_free, void(*)(void**));
    res->acquire = default_acquire;
    res->release = default_release;
    res->clear = default_clear;
    return res;
}

void shutdown(void) {
    __global_allocator__->clear(__global_allocator__);
//    __user_allocator__->clear(__user_allocator__);
//    __coop_allocator__->clear(__coop_allocator__);
}

Allocator *get_allocator(void) {
    if (__global_allocator__ == NULL) {
        fprintf(stderr, "You must use first init_coop() before doing anything.\n");
        exit(1);
    }
    return __global_allocator__;
}