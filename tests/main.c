//
// Created by danie on 28/05/2024.
//
#include <assert.h>
#include <string.h>
#include "../coop/globals.h"
#include "../coop/builtins/__init__.h"

void _main(void) {
    assert(strcmp(getattr(__global__field__name__field__name__, NAME)->data, NAME) == 0);
}

int main(void) {
    init_builtins();
    _main();
    get_allocator()->clear();
    return 0;
}