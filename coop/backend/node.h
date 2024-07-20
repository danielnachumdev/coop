//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_NODE_H
#define LOCAL_PLAYGROUND_NODE_H

#include "../builtins/macros.h"

typedef struct Node {
    void *data;
    struct Node *next;
    struct Node *prev;

    DuplicatorT(data_dup);

    ConsumerT(data_free);
} Node;

Node *node_new(void *data, DuplicatorT(data_dup), ConsumerT(data_free));

void node_free(Node **n);

#endif //LOCAL_PLAYGROUND_NODE_H
