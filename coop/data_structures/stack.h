//
// Created by danie on 02/06/2024.
//

#ifndef COOP_STACK_H
#define COOP_STACK_H

#include "../globals/macros.h"
#include "node.h"

typedef struct Stack {
    Duplicator(node_dup);

    Consumer(node_free);

    Node *top;
} Stack;

Stack *stack_new(Duplicator(node_dup), Consumer(node_free));

void stack_free(Stack **s);

void stack_push(Stack *s, const void *item);

void *stack_pop(Stack *s);

void *stack_top(Stack *s);

#endif //COOP_STACK_H
