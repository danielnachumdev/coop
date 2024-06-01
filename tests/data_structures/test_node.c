//
// Created by danie on 30/05/2024.
//

#include <malloc.h>
#include <assert.h>
#include "test_node.h"
#include "../../coop/data_structures/node.h"


void int_free(void *data) {
    free(data);
}

void *int_dup(const void *data) {
    int *new_int = (int *) malloc(sizeof(int));
    if (new_int) {
        *new_int = *(int *) data;
    }
    return new_int;
}

void test_node_creation_and_free() {
    int data = 42;

    Node *node = node_new(&data, int_dup, int_free);
    assert(node != NULL);
    assert(*(int *) (node->data) == 42);

    node_free(&node);
    assert(node == NULL);
}

void test_node_duplication() {
    int data = 24;

    Node *node = node_new(&data, int_dup, int_free);
    assert(node != NULL);
    assert(*(int *) (node->data) == 24);

    void *dup_data = node->data_dup(node->data);
    assert(*(int *) dup_data == 24);

    free(dup_data);
    node_free(&node);
    assert(node == NULL);
}

void test_node(void) {
    printf("Testing Node");
    test_node_creation_and_free();
    test_node_duplication();
    printf(" PASSED\n");
}