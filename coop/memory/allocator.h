//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_ALLOCATOR_H
#define LOCAL_PLAYGROUND_ALLOCATOR_H

#include <stdbool.h>

typedef enum AllocatorType {
    AllocatorLinkedList = 0,
    AllocatorHashSet
} AllocatorType;

typedef struct Allocator {
    AllocatorType allocator_type;
    void *structure;

    void *(*acquire)(unsigned long n);

    void *(*__impl_acquire)(void *structure, void *p);

    void (*release)(void *p);

    bool (*__impl_release)(void *structure, void *p);

    void (*clear)(struct Allocator *);

    void (*__impl_clear)(void **);
} Allocator;

extern unsigned long int allocated_bytes;
extern unsigned long int freed_bytes;

Allocator *get_allocator(void);

extern Allocator *__coop_allocator__;
extern Allocator *__user_allocator__;
extern Allocator *__global_allocator__;

Allocator *allocator_new_hashset(void);

Allocator *allocator_new_linkedlist(void);

void shutdown(void);

#define acquire(n) get_allocator()->acquire(n)
#define release(p) get_allocator()->release(p)
#endif //LOCAL_PLAYGROUND_ALLOCATOR_H
