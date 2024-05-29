//
// Created by t-danachum on 21/05/2024.
//
#include "../macros.h"
#include "linked_list.h"

LinkedList *linkedlist_new() {
    LinkedList *res = builtin_new(sizeof(LinkedList));
    if (res == NULL) return NULL;
    res->head = NULL;
    res->tail = NULL;
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

bool linkedlist_contains(const LinkedList *ll, const void *p, bool(*comparer)(const void *p1, const void *p2)) {
    if (ll == NULL || p == NULL) return false;

    Node *cur = ll->head;
    while (cur != NULL) {
        if (comparer(cur->data, p)) return true;
        cur = cur->next;
    }
    return false;
}

void naive_free(void *p) {
    builtin_free(p);
}

void *naive_dup(void *p) {
    return p;
}

Node *linkedlist_add(LinkedList *ll, void *p) {
    if (ll == NULL || p == NULL) return NULL;
    Node *res = node_new(p, naive_free, naive_dup);
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

void linkedlist_remove(LinkedList *ll, void *p) {
    if (ll == NULL || p == NULL) return;
    Node *cur = ll->head;
    while (cur != NULL) {
        if (cur->data == p) {
            if (cur == ll->head) {
                if (cur == ll->tail) {
                    ll->head = NULL;
                    ll->tail = NULL;
                }
                ll->head = ll->head->next;
            } else if (cur == ll->tail) {
                ll->tail = ll->tail->prev;
            } else {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
            }
            node_free(&cur);
            return;
        }
        cur = cur->next;
    }
}
