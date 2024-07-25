//
// Created by danie on 29/05/2024.
//
#include "coop/builtins/__init__.h"
#include "coop/__init__.h"

void _main(void) {
    Object *types[] = {Type, String, Integer, Number, Function, Field, Array, Boolean, Union};
    for (int i = 0; i < 9; ++i) {
        println(__new_string("Name ="), getattr(types[i], NAME), __new_string("dir ="));
        dir(types[i], false);
    }
}

int main() {
    coop_setup();
    _main();
    coop_teardown();
    return 0;
}

