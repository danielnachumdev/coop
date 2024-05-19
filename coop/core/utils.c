//
// Created by danie on 17/05/2024.
//
#include <string.h>
#include <stdarg.h>
#include "utils.h"
#include "builtins.h"
#include "memory_management//allocator.h"


//char *concatenate_strings(const char *a, const char *b) {
//    if (a == NULL || b == NULL) return NULL;
//    char *res = get_allocator()->allocate(strlen(a) + strlen(b)+1);
//    strcpy(res, a);
//    strcpy(res + strlen(a), b);
//    return res;
//}
Optional join_strings(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) return (Optional) {NULL};

    Optional o = acquire(strlen(s1) + strlen(s2) + 1);
    if (o.nullable != NULL) {
        strcpy(o.nullable, s1);
        strcpy(o.nullable + strlen(s1), s2);
    }
    return o;
}

Optional concatenate_strings(unsigned int n, ...) {
    va_list valist;
    va_start(valist, n);
    char *local_res = builtin_new(1);
    *local_res = '\0';
    for (unsigned int i = 0; i < n; i++) {
        char *cur = va_arg(valist, char *);
        char *new_res = builtin_new(strlen(local_res) + strlen(cur) + 1);
        if (new_res == NULL) {
            builtin_free(local_res);
            va_end(valist);
            return (Optional) {NULL};
        }
        strcpy(new_res, local_res);
        strcpy(new_res + strlen(local_res), cur);
        builtin_free(local_res);
        local_res = new_res;
    }
    char *res = acquire(strlen(local_res) + 1).nullable;
    if (res == NULL) {
        builtin_free(local_res);
        return (Optional) {NULL};
    }
    strcpy(res, local_res);
    builtin_free(local_res);
    va_end(valist);
    return (Optional) {res};
}

