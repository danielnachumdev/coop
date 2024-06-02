//
// Created by t-danachum on 02/06/2024.
//

#include <stdio.h>
#include <malloc.h>
#include "wrappers.h"

void *builtin_new_wrapper_impl(unsigned int n, const char *file, const unsigned int line) {
    printf("%-15s at line %4u: ", file, line);
    void *p = malloc(n);
    printf("Pointer = %p, Bytes = %5u\n", p, n);
    fflush(stdout);
    return p;
}