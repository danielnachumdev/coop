//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_NODE_H
#define LOCAL_PLAYGROUND_NODE_H

#include "../globals/macros.h"

typedef struct Node {
    void *data;
    struct Node *next;
    struct Node *prev;

    Duplicator(data_dup);

    Consumer(data_free);
} Node;

Node *node_new(void *data, Duplicator(data_dup), Consumer(data_free));

void node_free(Node **n);

#endif //LOCAL_PLAYGROUND_NODE_H
