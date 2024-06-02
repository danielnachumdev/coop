//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_LINKED_LIST_H
#define LOCAL_PLAYGROUND_LINKED_LIST_H

#include <stdbool.h>
#include "node.h"

#define ComparerT(name) __FUNCTION_POINTER_BUILDER(name,bool,const void *a,const void * b)

typedef struct DoublyLinkedList {
    Node *head;
    Node *tail;

    DuplicatorT(data_dup);

    ConsumerT(data_free);

    ComparerT(data_comparer);

} DoublyLinkedList;
typedef DoublyLinkedList LinkedList;

LinkedList *linkedlist_new(DuplicatorT(data_dup), ConsumerT(data_free), ComparerT(data_comparer));

void linkedlist_free(LinkedList **ll);

bool linkedlist_contains(const LinkedList *ll, const void *p);

Node *linkedlist_add(LinkedList *ll, void *p, ...);

bool linkedlist_remove(LinkedList *ll, void *p);

#define LINKEDLIST_FOREACH(cur_name, ll, body) EXPR( \
    Node * cur_name = ll->head;                    \
    while(cur_name != NULL){                      \
        Node * next = cur_name->next;              \
        {                                          \
        body                                           \
        }                                          \
        cur_name=next;                                               \
    }\
)


#endif //LOCAL_PLAYGROUND_LINKED_LIST_H
