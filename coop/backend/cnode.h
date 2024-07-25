//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_NODE_H
#define LOCAL_PLAYGROUND_NODE_H

#include "../builtins/macros.h"

typedef struct Node {
    void *data;
    struct CNode *next;
    struct CNode *prev;

    DuplicatorT(data_dup);

    ConsumerT(data_free);
} CNode;

CNode *cnode_new(const void *data, DuplicatorT(data_dup), ConsumerT(data_free));

void cnode_free(CNode **n);

#endif //LOCAL_PLAYGROUND_NODE_H
