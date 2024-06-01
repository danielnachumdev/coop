//
// Created by danie on 02/06/2024.
//

#include "stack.h"
#include "../globals/__init__.h"

Stack *stack_new(DuplicatorT(node_dup), ConsumerT(node_free)) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (stack == NULL) return NULL;
    stack->top = NULL;
    stack->node_free = node_free;
    stack->node_dup = node_dup;
    return stack;
}

void stack_free(Stack **s) {
    if (s == NULL || *s == NULL) return;
    Node *current = (*s)->top;
    while (current != NULL) {
        Node *temp = current;
        node_free(&temp);
        current = current->next;
    }
    free(*s);
    *s = NULL;
}

void stack_push(Stack *s, const void *item) {
    if (s == NULL || item == NULL) return;
    Node *new_node = acquire(sizeof(Node));
    if (new_node == NULL) return;
    new_node->data = s->node_dup(item);
    new_node->next = s->top;
    s->top = new_node;
}

void *stack_pop(Stack *s) {
    if (s == NULL || s->top == NULL) return NULL;
    Node *temp = s->top;
    s->top = s->top->next;
    void *data = s->node_dup(temp->data);
    node_free(&temp);
    return data;
}

void *stack_top(Stack *s) {
    if (s == NULL || s->top == NULL) return NULL;
    return s->top->data;
}
