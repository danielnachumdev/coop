//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_NODE_H
#define LOCAL_PLAYGROUND_NODE_H


typedef void(*NodeFreeFunc)(void *);

typedef void *(*NodeDupFunc)(void *);

typedef struct Node {
    void *data;
    struct Node *next;
    struct Node *prev;

    NodeFreeFunc free_func;

    NodeDupFunc dup_func;
} Node;

Node *node_new(void *data, NodeFreeFunc free_func, NodeDupFunc dup_func);

void node_free(Node **n);

#endif //LOCAL_PLAYGROUND_NODE_H
