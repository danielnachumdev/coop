//
// Created by danie on 02/06/2024.
//

#include "cstack.h"
#include "../memory/__init__.h"

Stack *cstack_new(DuplicatorT(data_dup), ConsumerT(data_free)) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (stack == NULL) return NULL;
    stack->top = NULL;
    stack->data_free = data_free;
    stack->data_dup = data_dup;
    return stack;
}

void cstack_free(Stack **s) {
    if (s == NULL || *s == NULL) return;
    CNode *cur = (*s)->top;
    while (cur != NULL) {
        CNode *next = cur->next;
        cnode_free(&cur);
        cur = next;
    }
    builtin_free(*s);
    *s = NULL;
}

void cstack_push(Stack *s, const void *item) {
    if (s == NULL || item == NULL) return;
    CNode *new_node = cnode_new(item, s->data_dup, s->data_free);
    new_node->next = s->top;
    s->top = new_node;
}

void *cstack_pop(Stack *s) {
    if (s == NULL || s->top == NULL) return NULL;
    CNode *temp = s->top;
    s->top = s->top->next;
    void *data = s->data_dup(temp->data);
    cnode_free(&temp);
    return data;
}

void *cstack_top(Stack *s) {
    if (s == NULL || s->top == NULL) return NULL;
    return s->top->data;
}
