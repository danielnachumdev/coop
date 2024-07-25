//
// Created by danie on 02/06/2024.
//

#ifndef COOP_CSTACK_H
#define COOP_CSTACK_H

#include "../builtins/macros.h"
#include "cnode.h"

typedef struct CStack {
    DuplicatorT(data_dup);

    ConsumerT(data_free);

    CNode *top;
} Stack;

Stack *cstack_new(DuplicatorT(node_dup), ConsumerT(node_free));

void cstack_free(Stack **s);

void cstack_push(Stack *s, const void *item);

void *cstack_pop(Stack *s);

void *cstack_top(Stack *s);

#endif //COOP_CSTACK_H
