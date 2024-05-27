//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_NODE_H
#define LOCAL_PLAYGROUND_NODE_H
typedef void *NodeData;

typedef void(*NodeFreeFunc)(NodeData);

typedef NodeData(*NodeDupFunc)(NodeData);

typedef struct Node {
    NodeData data;
    struct Node *next;
    struct Node *prev;

    NodeFreeFunc free_func;

    NodeDupFunc dup_func;
} Node;

Node *node_new(NodeData data, NodeFreeFunc free_func, NodeDupFunc dup_func);

void node_free(Node **n);

#endif //LOCAL_PLAYGROUND_NODE_H
