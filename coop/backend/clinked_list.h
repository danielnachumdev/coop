//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_LINKED_LIST_H
#define LOCAL_PLAYGROUND_LINKED_LIST_H

#include <stdbool.h>
#include "cnode.h"

#define ComparerT(name) __FUNCTION_POINTER_BUILDER(name,bool,const void *a,const void * b)

typedef struct DoublyLinkedList {
    CNode *head;
    CNode *tail;

    DuplicatorT(data_dup);

    ConsumerT(data_free);

    ComparerT(data_comparer);

} DoublyLinkedList;
typedef DoublyLinkedList CLinkedList;

CLinkedList *clinkedlist_new(DuplicatorT(data_dup), ConsumerT(data_free), ComparerT(data_comparer));

void clinkedlist_free(CLinkedList **ll);

bool clinkedlist_contains(const CLinkedList *ll, const void *p);

CNode *clinkedlist_add(CLinkedList *ll, void *p);

bool clinkedlist_remove(CLinkedList *ll, void *p);

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
