//
// Created by danie on 18/05/2024.
//
#include "_main.h"
#include "coop/__init__.h"

int main() {
    init_coop();
    _LOG("Starting main\n", DEBUG_LOG_SEVERITY);
    _main();
    _DEBUG("Finished main\n");
    shutdown();
    return 0;
}



