//
// Created by danie on 30/05/2024.
//

#include <assert.h>
#include <stddef.h>
#include <malloc.h>
#include <stdio.h>
#include "test_linkedlist.h"
#include "../../coop/backend/clinked_list.h"

bool linkedlist_int_comparer(const void *p1, const void *p2) {
    return *(int *) p1 == *(int *) p2;
}

void linkedlist_integer_free(void *p) {
    builtin_free(p);
}

void *linkedlist_integer_dup(const void *p) {
    int *res = builtin_new(sizeof(int));
    *res = *(int *) p;
    return res;
}

void test_linkedlist_creation_and_free() {
    CLinkedList *ll = clinkedlist_new(linkedlist_integer_dup, linkedlist_integer_free, linkedlist_int_comparer);
    assert(ll != NULL);
    assert(ll->head == NULL);
    assert(ll->tail == NULL);

    clinkedlist_free(&ll);
    assert(ll == NULL);
}

void test_linkedlist_add_and_contains() {
    CLinkedList *ll = clinkedlist_new(linkedlist_integer_dup, linkedlist_integer_free, linkedlist_int_comparer);
    assert(ll != NULL);

    int data1 = 10;
    CNode *node1 = clinkedlist_add(ll, &data1);
    assert(node1 != NULL);
    assert(clinkedlist_contains(ll, &data1));

    int data2 = 20;
    CNode *node2 = clinkedlist_add(ll, &data2);
    assert(node2 != NULL);
    assert(clinkedlist_contains(ll, &data2));

    clinkedlist_free(&ll);
}

void test_linkedlist_remove() {
    CLinkedList *ll = clinkedlist_new(linkedlist_integer_dup, linkedlist_integer_free, linkedlist_int_comparer);
    assert(ll != NULL);

    int data1 = 10;
    clinkedlist_add(ll, &data1);

    int data2 = 20;
    clinkedlist_add(ll, &data2);

    clinkedlist_remove(ll, &data1);
    assert(not(clinkedlist_contains(ll, &data1)));
    assert(clinkedlist_contains(ll, &data2));

    clinkedlist_remove(ll, &data2);
    assert(not(clinkedlist_contains(ll, &data2)));

    clinkedlist_free(&ll);
}

void test_linkedlist(void) {
    printf("Testing CLinkedList - STARTED\n");
    test_linkedlist_creation_and_free();
    test_linkedlist_add_and_contains();
    test_linkedlist_remove();
    printf("Testing CLinkedList - PASSED\n");
}