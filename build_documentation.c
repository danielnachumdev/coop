//
// Created by danie on 29/05/2024.
//
#include "coop/__init__.h"

int main() {
    Object *types[] = {Array, Boolean, Function, Integer, List, Node, Number, Set, String, Type, Union};
    for (int i = 0; i < 11; ++i) {
        println(igetfunc(String, __init__)("Name ="), getattr(types[i], "__name__"));
        dir(types[i]);
    }
    return 0;
}

