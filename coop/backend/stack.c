//
// Created by danie on 02/06/2024.
//

#include "stack.h"
#include "../memory/__init__.h"

Stack *stack_new(DuplicatorT(data_dup), ConsumerT(data_free)) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (stack == NULL) return NULL;
    stack->top = NULL;
    stack->data_free = data_free;
    stack->data_dup = data_dup;
    return stack;
}

void stack_free(Stack **s) {
    if (s == NULL || *s == NULL) return;
    Node *cur = (*s)->top;
    while (cur != NULL) {
        Node *next = cur->next;
        node_free(&cur);
        cur = next;
    }
    builtin_free(*s);
    *s = NULL;
}

void stack_push(Stack *s, const void *item) {
    if (s == NULL || item == NULL) return;
    Node *new_node = node_new(item, s->data_dup, s->data_free);
    new_node->next = s->top;
    s->top = new_node;
}

void *stack_pop(Stack *s) {
    if (s == NULL || s->top == NULL) return NULL;
    Node *temp = s->top;
    s->top = s->top->next;
    void *data = s->data_dup(temp->data);
    node_free(&temp);
    return data;
}

void *stack_top(Stack *s) {
    if (s == NULL || s->top == NULL) return NULL;
    return s->top->data;
}
