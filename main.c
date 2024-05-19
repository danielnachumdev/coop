//
// Created by danie on 18/05/2024.
//
#include "coop/core/logging/logger.h"
#include "coop/core/memory_management/allocator.h"
#include "entry_point.h"


int main(void) {
    get_logger()->debug("Starting \"Main\"\n");
    entry_point();
    get_logger()->debug("Exiting \"Main\"\n");
    get_allocator()->clean();
    return 0;
}



