//
// Created by danie on 29/05/2024.
//
#include "coop/globals/__init__.h"
#include "coop/builtins/__init__.h"
#include "coop/__init__.h"

void _main(void) {
    Object *types[] = {Type, String, Integer, Number, Function, Field, Array, Boolean, Union};
    for (int i = 0; i < 9; ++i) {
        println(new_string("Name ="), getattr(types[i], NAME), new_string("dir ="), dir(types[i]));
    }
}

int main() {
    init_coop();
    _main();
    get_allocator()->clear();
    return 0;
}

