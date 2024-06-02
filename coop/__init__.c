//
// Created by danie on 30/05/2024.
//

#include "__init__.h"
#include "builtins/__init__.h"

void init_coop(void) {
    __global_allocator__ = __coop_allocator__ = allocator_new_linkedlist();;
    init_builtins();
    __global_allocator__ = __user_allocator__ = allocator_new_hashset();
}