//
// Created by danie on 16/05/2024.
//

#include "linked_list.h"
#include "../exceptions/exception.h"
#include "../builtins.h"
#include "../utils.h"

Node *linked_list_get(LinkedList *ll, void *p) {
    if (ll == NULL)return NULL;
    Node *cur = ll->head;
    while (cur != NULL) {
        if (cur->data == p)
            return cur;
        cur = cur->next;
    }
    return cur;
}

LinkedList *linked_list_new() {
    LinkedList *res = builtin_new(sizeof(LinkedList));
    if (res == NULL) return NULL;
    res->head = NULL;
    res->tail = NULL;
    return res;
}

void linked_list_free(LinkedList **pp_ll) {
    if (pp_ll == NULL) return;
    LinkedList *p_ll = *pp_ll;
    if (p_ll == NULL) return;

    Node *cur = p_ll->head;
    while (cur != NULL) {
        Node *next = cur->next;
        node_free(&cur);
        cur = next;
    }

    free(p_ll);
    *pp_ll = NULL;
}

Node *linked_list_append(LinkedList *ll, void *p) {
    if (ll == NULL || p == NULL) return NULL;
    if (ll->head == NULL) {
        ll->head = node_new();
        if (ll->head == NULL) {
            get_allocator()->clean();
            easy_throw("Failed Allocation", "Failed allocating allocate object");
        }
        ll->tail = ll->head;
        ll->head->data = p;
        ll->head->next = NULL;
        ll->head->prev = NULL;
        ll->head->free_func = free;
    } else {
        Node *new_tail = node_new();
        if (ll->head == NULL) {
            get_allocator()->clean();
            easy_throw("Failed Allocation", "Failed allocating allocate object");
        }
        new_tail->data = p;
        new_tail->free_func = free;
        new_tail->next = NULL;
        new_tail->prev = ll->tail;
        ll->tail->next = new_tail;
        ll->tail = new_tail;
    }
    return ll->tail;
}


void random_access_linked_list_free(IRandomAccess *self) {
    linked_list_free((LinkedList **) &(self->data_structure));
}

void *random_access_linked_list_at(IRandomAccess *self, long unsigned int index) {
    LinkedList *ll = self->data_structure;
    long unsigned int length = self->length(self);
    if (index >= length) easy_throw("IndexError", "Index is out of bounds");
    long unsigned int i = 0;
    Node *cur = ll->head;
    while (i < index) {
        cur = cur->next;
        i += 1;
    }
    return cur->data;
}

long unsigned int random_access_linked_list_length(IRandomAccess *self) {
    LinkedList *ll = self->data_structure;
    long unsigned int res = 0;
    Node *cur = ll->head;
    while (cur != NULL) {
        cur = cur->next;
        res += 1;
    }
    return res;
}

void *random_access_linked_list_contains(IRandomAccess *self, void *p) {
    return linked_list_get(self->data_structure, p);
}

void *random_access_linked_list_append(IRandomAccess *self, void *p) {
    return linked_list_append(self->data_structure, p);
}

void *random_access_linked_list_insert(IRandomAccess *self, void *p, long unsigned int index) {

}

void random_access_linked_list_remove(IRandomAccess *self, void *p) {
    LinkedList *ll = self->data_structure;
    Node *res = linked_list_get(ll, p);
    if (res == NULL) return;
    long unsigned int length = self->length(self);
    if (length == 1) {
        ll->head = NULL;
        ll->tail = NULL;
    } else {
        if (res == ll->head) {
            ll->head = ll->head->next;
            ll->head->prev = NULL;
        } else if (res == ll->tail) {
            ll->tail = ll->tail->prev;
            ll->tail->next = NULL;
        } else {
            res->prev->next = res->next;
            res->next->prev = res->prev;
        }
    }
    node_free(&res);
}


IRandomAccess random_access_linked_list = {
        .data_structure=NULL,
        .free_structure=random_access_linked_list_free,
        .at=random_access_linked_list_at,
        .length=random_access_linked_list_length,
        .contains=random_access_linked_list_contains,
        .append=random_access_linked_list_append,
        .insert=random_access_linked_list_insert,
        .remove=random_access_linked_list_remove
};