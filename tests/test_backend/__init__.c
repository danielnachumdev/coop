//
// Created by danie on 30/05/2024.
//

#include <stdio.h>
#include "__init__.h"
#include "test_node.h"
#include "test_linkedlist.h"
#include "test_hashset.h"
#include "test_stack.h"

void test_backend(void) {
    printf("============================TESTING BACKEND==========================\n");
    test_node();
    test_linkedlist();
    test_hashset();
    test_stack();
    printf("==========================FINISHED TESTING BACKEND============================\n");
}