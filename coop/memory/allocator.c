//
// Created by t-danachum on 21/05/2024.
//

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "allocator.h"
#include "../builtins/macros.h"
#include "../backend/chashset.h"

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
    printf("Total bytes allocated = %lu\n", allocated_bytes);
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
    res->structure = chashset_new(naive_dup__, naive_free__, default_chashset_pointer_comparer,
                                  &default_chashset_strategy,
                                  pointer_hash);
    if (res->structure == NULL) {
        builtin_free(res);
        return NULL;
    }
    res->__impl_acquire = cast(chashset_add_impl, void *(*)(void *, void *));
    res->__impl_release = cast(chashset_remove, bool(*)(void*, void*));
    res->__impl_clear = cast(chashset_free, void(*)(void**));
    res->acquire = default_acquire;
    res->release = default_release;
    res->clear = default_clear;
    return res;
}

Allocator *allocator_new_linkedlist(void) {
    Allocator *res = builtin_new(sizeof(Allocator));
    if (res == NULL) return NULL;
    res->structure = clinkedlist_new(naive_dup__, naive_free__, default_chashset_pointer_comparer);
    res->allocator_type = AllocatorLinkedList;
    if (res->structure == NULL) {
        builtin_free(res);
        return NULL;
    }
    res->__impl_acquire = cast(clinkedlist_add, void *(*)(void *, void *));
    res->__impl_release = cast(clinkedlist_remove, bool(*)(void*, void*));
    res->__impl_clear = cast(clinkedlist_free, void(*)(void**));
    res->acquire = default_acquire;
    res->release = default_release;
    res->clear = default_clear;
    return res;
}


Allocator *get_allocator(void) {
    if (__global_allocator__ == NULL) {
        fprintf(stderr, "You must use first coop_setup() before doing anything.\n");
        exit(1);
    }
    return __global_allocator__;
}