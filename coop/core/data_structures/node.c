//
// Created by danie on 16/05/2024.
//

#include <malloc.h>
#include "node.h"
#include "../builtins.h"

Node *node_new() {
    //Explicitly dont use get_allocator()->new because then it will recurse infinitely
    Node *res = builtin_new(sizeof(Node));
    res->next = NULL;
    res->free_func = NULL;
    res->data = NULL;
    res->prev = NULL;
    return res;
}

void node_free(Node **pp_n) {
    if (pp_n == NULL) return;
    if (*pp_n == NULL) return;
    (*pp_n)->free_func((*pp_n)->data);
    builtin_free(*pp_n);
    *pp_n = NULL;
}