//
// Created by danie on 02/06/2024.
//

#ifndef COOP_STACK_H
#define COOP_STACK_H

#include "../builtins/macros.h"
#include "node.h"

typedef struct Stack {
    DuplicatorT(data_dup);

    ConsumerT(data_free);

    Node *top;
} Stack;

Stack *stack_new(DuplicatorT(node_dup), ConsumerT(node_free));

void stack_free(Stack **s);

void stack_push(Stack *s, const void *item);

void *stack_pop(Stack *s);

void *stack_top(Stack *s);

#endif //COOP_STACK_H
