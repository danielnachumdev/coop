//
// Created by danie on 18/05/2024.
//

#include "print.h"
#include <stdio.h>
#include <stdarg.h>

#include "core/utils.h"
#include "core/macros.h"
#include "core/logging/logger.h"

void print_imp(const char *sep, const char *end, unsigned int n, ...) {
    RETURN_DO_IF(n == 0, {
        fprintf(stdout, "%s", end);
    });
    va_list valist;
    va_start(valist, n);
    Optional res = {va_arg(valist, char *)};
    for (unsigned int i = 1; i < n; ++i) {
        RETURN_DO_IF(res.nullable == NULL, {
            _WARN("'print' function failed.\n");
            va_end(valist);
        });
        res = join_strings(res.nullable, sep);
        RETURN_DO_IF(res.nullable == NULL, {
            _WARN("'print' function failed.\n");
            va_end(valist);
        });
        char *cur = va_arg(valist, char *);
        res = join_strings(res.nullable, cur);
    }
    va_end(valist);
    RETURN_DO_IF(res.nullable == NULL, {
        _WARN("'print' function failed.\n");
    });
    if (res.nullable == NULL) return;
    fprintf(stdout, "%s%s", (char *) res.nullable, end);
}