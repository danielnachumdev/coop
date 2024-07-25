//
// Created by danie on 30/05/2024.
//

#include "__init__.h"

typedef enum RunStatus {
    NOT_RUNNING,
    RUNNING,
} RunStatus;

static RunStatus global_status = NOT_RUNNING;

__attribute__((constructor)) void coop_setup(void) {
    if (global_status != NOT_RUNNING) return;
    __global_allocator__ = __coop_allocator__ = allocator_new_linkedlist();;
    init_builtins();
//    __global_allocator__ = __user_allocator__ = allocator_new_hashset();
    _LOG("Starting main\n", DEBUG_LOG_SEVERITY);
    global_status = RUNNING;
}

__attribute__((destructor)) void coop_teardown(void) {
    if (global_status != RUNNING) return;
    _DEBUG("Finished main\n");
    __global_allocator__->clear(__global_allocator__);
//    __user_allocator__->clear(__user_allocator__);
//    __coop_allocator__->clear(__coop_allocator__);
    global_status = NOT_RUNNING;
}