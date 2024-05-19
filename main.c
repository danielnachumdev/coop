//
// Created by danie on 18/05/2024.
//
#include "coop/core/logging/logger.h"
#include "coop/core/memory_management/allocator.h"
#include "_main.h"


int main(void) {
    get_logger()->debug("Starting \"Main\"\n");
    _main();
    get_logger()->debug("Exiting \"Main\"\n");
    get_allocator()->clean();
    return 0;
}



