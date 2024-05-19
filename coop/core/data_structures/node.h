//
// Created by danie on 16/05/2024.
//

#ifndef MACROPYTHON_NODE_H
#define MACROPYTHON_NODE_H
typedef struct Node {
    void *data;

    void (*free_func)(void *data);

    struct Node *next;
    struct Node *prev;
} Node;

Node *node_new();

void node_free(Node **);

#endif //MACROPYTHON_NODE_H
