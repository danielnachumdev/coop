//
// Created by t-danachum on 21/05/2024.
//

#include <stddef.h>
#include "node.h"
#include "../globals/macros.h"


Node *node_new(void *data, NodeFreeFunc free_func, NodeDupFunc dup_func) {
    if (data == NULL || free_func == NULL || dup_func == NULL) return NULL;
    Node *res = builtin_new(sizeof(Node));
    if (res == NULL) return NULL;
    res->data = dup_func(data);
    if (res->data == NULL) {
        builtin_free(res);
        return NULL;
    }
    res->dup_func = dup_func;
    res->free_func = free_func;
    res->next = NULL;
    res->prev = NULL;
    return res;
}

void node_free(Node **n) {
    if (n == NULL || *n == NULL) return;
    (*n)->free_func((*n)->data);
    builtin_free(*n);
    *n = NULL;
}
