//
// Created by danie on 29/05/2024.
//
#include "coop/builtins/__init__.h"
#include "coop/__init__.h"

void _main(void) {
    Object *types[] = {Type, String, Integer, Number, Function, Array, Boolean, Union};
    for (int i = 0; i < 9; ++i) {
        println(explicitgetfunc(String, __init__)("Name ="), getattr(types[i], "__name__"));
        dir(types[i]);
    }
}

int main() {
    coop_setup();
    _main();
    coop_teardown();
    return 0;
}

