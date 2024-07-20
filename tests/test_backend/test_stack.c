//
// Created by danie on 02/06/2024.
//

#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "test_stack.h"
#include "../../coop/backend/stack.h"

void *int_duplicator(const void *item) {
    int *ptr = (int *) malloc(sizeof(int));
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    *ptr = *((int *) item);
    return ptr;
}

// Test function for stack operations
void test_stack(void) {
    printf("Testing Stack - STARTED\n");
    // Create a new stack
    Stack *stack = stack_new(int_duplicator, free);

    // Test empty stack
    assert(stack_top(stack) == NULL);

    // Push items onto the stack
    int a = 10, b = 20, c = 30;
    stack_push(stack, &a);
    stack_push(stack, &b);
    stack_push(stack, &c);

    // Test stack top
    assert(*((int *) stack_top(stack)) == 30);

    // Test stack pop
    int *popped_item = (int *) stack_pop(stack);
    assert(*popped_item == 30);
    free(popped_item);

    // Test stack top after pop
    assert(*((int *) stack_top(stack)) == 20);

    // Free the stack
    stack_free(&stack);

    // Test empty stack after free
    assert(stack == NULL);
    printf("Testing Stack - PASSED\n");
}