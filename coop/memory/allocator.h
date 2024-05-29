//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_ALLOCATOR_H
#define LOCAL_PLAYGROUND_ALLOCATOR_H

typedef struct Allocator {
    void *structure;

    void *(*acquire)(unsigned long n);

    void (*release)(void *p, unsigned int size_in_bytes);

    void (*clear)(void);
} Allocator;

extern unsigned long int allocated_bytes;
extern unsigned long int freed_bytes;

Allocator *get_allocator(void);

#define acquire(n) get_allocator()->acquire(n)
#define release(p) get_allocator()->release(p, p != NULL ? sizeof(*p) : 0)
#endif //LOCAL_PLAYGROUND_ALLOCATOR_H
