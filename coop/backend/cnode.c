//
// Created by t-danachum on 21/05/2024.
//

#include <stddef.h>
#include "cnode.h"
#include "../builtins/macros.h"


CNode *cnode_new(const void *data, DuplicatorT(data_dup), ConsumerT(data_free)) {
    if (data == NULL || data_dup == NULL || data_free == NULL) return NULL;
    CNode *res = builtin_new(sizeof(CNode));
    if (res == NULL) return NULL;
    res->data = data_dup(data);
    if (res->data == NULL) {
        builtin_free(res);
        return NULL;
    }
    res->data_dup = data_dup;
    res->data_free = data_free;
    res->next = NULL;
    res->prev = NULL;
    return res;
}

void cnode_free(CNode **n) {
    if (n == NULL || *n == NULL) return;
    (*n)->data_free((*n)->data);
    builtin_free(*n);
    *n = NULL;
}
