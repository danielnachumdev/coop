//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_LINKED_LIST_H
#define LOCAL_PLAYGROUND_LINKED_LIST_H

#include <stdbool.h>
#include "node.h"

typedef struct DoublyLinkedList {
    Node *head;
    Node *tail;
} DoublyLinkedList;
typedef DoublyLinkedList LinkedList;

LinkedList *linkedlist_new();

void linkedlist_free(LinkedList **ll);

bool linkedlist_contains(const LinkedList *ll, const void *p, bool(*comparer)(const void *p1, const void *p2));

Node *linkedlist_add(LinkedList *ll, void *p);

void linkedlist_remove(LinkedList *ll, void *p);

#endif //LOCAL_PLAYGROUND_LINKED_LIST_H
