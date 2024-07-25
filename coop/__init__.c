//
// Created by danie on 30/05/2024.
//

#include "__init__.h"

static bool completed_setup = false;

__attribute__((constructor)) void coop_setup(void) {
    if (completed_setup) return;
    __global_allocator__ = __coop_allocator__ = allocator_new_linkedlist();;
    init_builtins();
//    __global_allocator__ = __user_allocator__ = allocator_new_hashset();
    _LOG("Starting main\n", DEBUG_LOG_SEVERITY);
    completed_setup = true;
}

__attribute__((destructor)) void coop_teardown(void) {
    if (not(completed_setup)) return;
    _DEBUG("Finished main\n");
    __global_allocator__->clear(__global_allocator__);
//    __user_allocator__->clear(__user_allocator__);
//    __coop_allocator__->clear(__coop_allocator__);
}