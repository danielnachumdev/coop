//
// Created by t-danachum on 21/05/2024.
//
#include "../globals/macros.h"
#include "linked_list.h"

LinkedList *linkedlist_new(DuplicatorT(data_dup), ConsumerT(data_free), ComparerT(data_comparer)) {
    if (data_dup == NULL || data_free == NULL || data_comparer == NULL) return NULL;
    LinkedList *res = builtin_new(sizeof(LinkedList));
    if (res == NULL) return NULL;
    res->head = NULL;
    res->tail = NULL;
    res->data_dup = data_dup;
    res->data_free = data_free;
    res->data_comparer = data_comparer;
    return res;
}

void linkedlist_free(LinkedList **ll) {
    if (ll == NULL || *ll == NULL) return;
    Node *cur = (*ll)->head;
    while (cur != NULL) {
        Node *next = cur->next;
        node_free(&cur);
        cur = next;
    }
    builtin_free(*ll);
    *ll = NULL;
}

bool linkedlist_contains(const LinkedList *ll, const void *p) {
    if (ll == NULL || p == NULL) return false;
    LINKEDLIST_FOREACH(cur, ll, {
        if (ll->data_comparer(cur->data, p)) return true;
    });
    return false;
}

Node *linkedlist_add(LinkedList *ll, void *p) {
    if (ll == NULL || p == NULL) return NULL;
    Node *res = node_new(p, ll->data_dup, ll->data_free);
    if (res == NULL) return NULL;
    if (ll->head == NULL) {
        ll->head = res;
        ll->tail = res;
    } else {
        Node *prev_head = ll->head;
        ll->head = res;
        res->next = prev_head;
        prev_head->prev = res;
    }
    return res;
}

bool linkedlist_remove(LinkedList *ll, void *p) {
    if (ll == NULL || p == NULL) return false;
    Node *cur = ll->head;
    while (cur != NULL) {
        Node *next = cur->next;
        if (ll->data_comparer(cur->data, p)) {
            if (cur == ll->head) {
                if (cur == ll->tail)
                    ll->tail = NULL;
                ll->head->prev = NULL;
                ll->head = ll->head->next;
            } else if (cur == ll->tail) {
                ll->tail->prev->next = NULL;
                ll->tail = ll->tail->prev;
            } else {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
            }
            node_free(&cur);
            return true;
        }
        cur = next;
    }
    return false;
}
