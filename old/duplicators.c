//
// Created by danie on 19/05/2024.
//

#include <string.h>
#include "duplicators.h"
#include "core/memory/allocator.h"

char *duplicate_string(const char *s) {
    char *res = acquire(sizeof(char) * strlen(s) + 1).nullable;
    if (res != NULL)
        strcpy(res, s);
    return res;
}

int *duplicate_integer(const int *n) {
    return (int *) duplicate_string((const char *) n);
}