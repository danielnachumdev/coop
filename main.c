//
// Created by danie on 18/05/2024.
//
#include "_main.h"
#include "coop/memory/allocator.h"
#include "coop/log/logger.h"
#include "coop/builtins/__init__.h"

int main() {
    _DEBUG("Starting main\n");
    init_builtins();
    _main();
    _DEBUG("Finished main\n");
    get_allocator()->clean();
    return 0;
}



