//
// Created by danie on 16/05/2024.
//

#ifndef MACROPYTHON_LINKED_LIST_H
#define MACROPYTHON_LINKED_LIST_H

#include "node.h"
#include "../memory_management/allocator.h"
#include "interface_random_access.h"

typedef struct DoublyLinkedList {
    Node *head;
    Node *tail;
} DoublyLinkedList;

typedef DoublyLinkedList LinkedList;

LinkedList *linked_list_new();

void linked_list_free(LinkedList **);

Node *linked_list_get(LinkedList *, void *);

Node *linked_list_append(LinkedList *ll, void *p);

extern IRandomAccess random_access_linked_list;
#endif //MACROPYTHON_LINKED_LIST_H
