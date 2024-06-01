//
// Created by danie on 18/05/2024.
//
#include "_main.h"
#include "coop/__init__.h"

int main() {
    _DEBUG("Starting main\n");
    init_coop();
    _main();
    _DEBUG("Finished main\n");
    get_allocator()->clear();
    return 0;
}



