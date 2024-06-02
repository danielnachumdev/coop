//
// Created by danie on 30/05/2024.
//

#include <assert.h>
#include <stddef.h>
#include <malloc.h>
#include <stdio.h>
#include "test_linkedlist.h"
#include "../../coop/data_structures/linked_list.h"

bool linkedlist_int_comparer(const void *p1, const void *p2) {
    return *(int *) p1 == *(int *) p2;
}

void linkedlist_naive_free(void *p) {
    builtin_free(p);
}

void *linkedlist_naive_dup(const void *p) {
    return (void *) p;
}

void test_linkedlist_creation_and_free() {
    LinkedList *ll = linkedlist_new(linkedlist_naive_dup, linkedlist_naive_free, linkedlist_int_comparer);
    assert(ll != NULL);
    assert(ll->head == NULL);
    assert(ll->tail == NULL);

    linkedlist_free(&ll);
    assert(ll == NULL);
}

void test_linkedlist_add_and_contains() {
    LinkedList *ll = linkedlist_new(linkedlist_naive_dup, linkedlist_naive_free, linkedlist_int_comparer);
    assert(ll != NULL);

    int *data1 = (int *) malloc(sizeof(int));
    *data1 = 10;
    Node *node1 = linkedlist_add(ll, data1);
    assert(node1 != NULL);
    assert(linkedlist_contains(ll, data1));

    int *data2 = (int *) malloc(sizeof(int));
    *data2 = 20;
    Node *node2 = linkedlist_add(ll, data2);
    assert(node2 != NULL);
    assert(linkedlist_contains(ll, data2));

    linkedlist_free(&ll);
}

void test_linkedlist_remove() {
    LinkedList *ll = linkedlist_new(linkedlist_naive_dup, linkedlist_naive_free, linkedlist_int_comparer);
    assert(ll != NULL);

    int *data1 = (int *) malloc(sizeof(int));
    *data1 = 10;
    linkedlist_add(ll, data1);

    int *data2 = (int *) malloc(sizeof(int));
    *data2 = 20;
    linkedlist_add(ll, data2);

    linkedlist_remove(ll, data1);
    assert(!linkedlist_contains(ll, data1));
    assert(linkedlist_contains(ll, data2));

    linkedlist_remove(ll, data2);
    assert(!linkedlist_contains(ll, data2));

    linkedlist_free(&ll);
}

void test_linkedlist(void) {
    printf("Testing LinkedList");
    test_linkedlist_creation_and_free();
    test_linkedlist_add_and_contains();
    test_linkedlist_remove();
    printf(" PASSED\n");
}