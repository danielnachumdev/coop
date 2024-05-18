//
// Created by danie on 16/05/2024.
//

#include <malloc.h>
#include <stdlib.h>
#include "allocator.h"
#include "../exceptions/exception.h"
#include "../logging/logger.h"
#include "../builtins.h"

static Allocator *global_allocator = NULL;

Optional allocator_new(long unsigned int size) {
    if (size <= 0) return (Optional) {NULL};
    void *p = builtin_new(size);
    if (p != NULL)
        global_allocator->structure->append(global_allocator->structure, p);
    return (Optional) {p}; // whether it is NULL or not we should still return it
}

void allocator_free(void *p) {
    if (p == get_logger()) {
        get_logger()->warn(
                "The GlobalLogger is automatically freed at the end of the runtime and should not be manually freed!\n");
        return;
    }
    global_allocator->structure->remove(global_allocator->structure, p);
}

void allocator_clean(void) {
    get_logger()->debug("Cleaning up...\n");
    //Explicitly not using get_allocator()->free
    global_allocator->structure->free_structure(global_allocator->structure);
    builtin_free(global_allocator->structure);
    builtin_free(global_allocator);
}

void init_allocator(void) {
    //IMPORTANT to explicitly not use 'throw' (or something that uses it under the hood)
    // if we get an exception
    global_allocator = (Allocator *) builtin_new(sizeof(Allocator));
    if (global_allocator == NULL) {
        fprintf(stderr, "%s at line number %d: %s(%s)\n", __FILE__, __LINE__, "FailedAllocation",
                "Failed allocating the global_allocator");
        exit(1);
    }
    global_allocator->structure = builtin_new(sizeof(IRandomAccess));
    if (global_allocator->structure == NULL) {
        builtin_free(global_allocator);
        fprintf(stderr, "%s at line number %d: %s(%s)\n", __FILE__, __LINE__, "FailedAllocation",
                "Failed allocating memory for the global allocator's data data_structure");
        exit(1);
    }
    *(global_allocator->structure) = random_access_linked_list;
    global_allocator->structure->data_structure = linked_list_new();
    global_allocator->new = allocator_new;
    global_allocator->free = allocator_free;
    global_allocator->clean = allocator_clean;
}

Allocator *get_allocator(void) {
    if (global_allocator != NULL) return global_allocator;
    init_allocator();
    // From here get_allocator will work correctly in other places so it's okay to use stuff that use it
    get_logger()->debug("Successfully Initialized GlobalAllocator and GlobalLogger!\n");
    return global_allocator;
}