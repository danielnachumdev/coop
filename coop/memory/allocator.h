//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_ALLOCATOR_H
#define LOCAL_PLAYGROUND_ALLOCATOR_H

typedef struct Allocator {
    void *structure;

    void *(*acquire)(unsigned long);

    void (*release)(void *);

    void (*clear)(void);
} Allocator;

Allocator *get_allocator(void);

#define acquire(n) get_allocator()->acquire(n)
#define release(p) get_allocator()->release(p)
#endif //LOCAL_PLAYGROUND_ALLOCATOR_H
