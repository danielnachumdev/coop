//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_ALLOCATOR_H
#define LOCAL_PLAYGROUND_ALLOCATOR_H
#include <stdbool.h>

typedef struct Allocator {
    void *structure;

    void *(*acquire)(unsigned long n, ... /*bool keep_allocated_address_constant*/);

    void (*release)(void *p);

    void (*clear)(void);
} Allocator;

extern unsigned long int allocated_bytes;
extern unsigned long int freed_bytes;

Allocator *get_allocator(void);

#define acquire(n, ...) get_allocator()->acquire(n, ## __VA_ARGS__ , false)
#define release(p) get_allocator()->release(p)
#endif //LOCAL_PLAYGROUND_ALLOCATOR_H
