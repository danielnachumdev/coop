//
// Created by t-danachum on 21/05/2024.
//
#include "../builtins/macros.h"
#include "clinked_list.h"

CLinkedList *clinkedlist_new(DuplicatorT(data_dup), ConsumerT(data_free), ComparerT(data_comparer)) {
    if (data_dup == NULL || data_free == NULL || data_comparer == NULL) return NULL;
    CLinkedList *res = builtin_new(sizeof(CLinkedList));
    if (res == NULL) return NULL;
    res->head = NULL;
    res->tail = NULL;
    res->data_dup = data_dup;
    res->data_free = data_free;
    res->data_comparer = data_comparer;
    return res;
}

void clinkedlist_free(CLinkedList **ll) {
    if (ll == NULL || *ll == NULL) return;
    CNode *cur = (*ll)->head;
    int index = 0;
    while (cur != NULL) {
        CNode *next = cur->next;
        cnode_free(&cur);
        cur = next;
        index += 1;
    }
    builtin_free(*ll);
    *ll = NULL;
}

bool clinkedlist_contains(const CLinkedList *ll, const void *p) {
    if (ll == NULL || p == NULL) return false;
    CNode *cur = ll->head;
    while (cur != NULL) {
        CNode *next = cur->next;
        if (ll->data_comparer(cur->data, p))
            return true;
        cur = next;
    }
    return false;
}

unsigned int allocation_index = 0;

CNode *clinkedlist_add(CLinkedList *ll, void *p) {
    if (ll == NULL || p == NULL) return NULL;
    CNode *res = cnode_new(p, ll->data_dup, ll->data_free);
    if (res == NULL) return NULL;
    if (ll->head == NULL) {
        ll->head = res;
        ll->tail = res;
    } else {
        CNode *prev_head = ll->head;
        ll->head = res;
        res->next = prev_head;
        prev_head->prev = res;
    }
    allocation_index += 1;
    return res;
}

bool clinkedlist_remove(CLinkedList *ll, void *p) {
    if (ll == NULL || p == NULL) return false;
    CNode *cur = ll->head;
    while (cur != NULL) {
        CNode *next = cur->next;
        if (ll->data_comparer(cur->data, p)) {
            if (cur == ll->head) {
                if (cur == ll->tail)
                    ll->tail = NULL;
                else
                    ll->head->next->prev = NULL;
                ll->head = ll->head->next;
            } else if (cur == ll->tail) {
                ll->tail->prev->next = NULL;
                ll->tail = ll->tail->prev;
            } else {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
            }
            cnode_free(&cur);
            return true;
        }
        cur = next;
    }
    return false;
}
