//
// Created by danie on 28/05/2024.
//

#include <stdio.h>
#include <stdarg.h>
#include "../../object.h"
#include "../attr/getattr.h"

#include "../../types/Array.h"
#include "../../macros.h"
#include "../../types/__init__.h"

void __print_object(Object *obj) {
    if (obj == NULL) printf("NULL");
    else if (obj->type == Type) igetfunc(Type, __print__)(obj);
    else if (obj->type == Array) igetfunc(Array, __print__)(obj);
    else if (obj->type == Number) number_print(obj);
    else if (obj->type == Boolean)  igetfunc(Boolean, __print__)(obj);
    else if (obj->type == Integer) igetfunc(Integer, __print__)(obj);
    else if (obj->type == String) igetfunc(String, __print__)(obj);
    else if (obj->type == Union) igetfunc(Union, __print__)(obj);
    else if (obj->type == Function) igetfunc(Function, __print__)(obj);
    else printf("Object %p", obj);
}


void _print_imp(const char *sep, const char *end, unsigned int n, ...) {
    if (sep == NULL || end == NULL) return;
    va_list valist;
    va_start(valist, n);
    for (unsigned int i = 0; i < n; ++i) {
        Object *cur = va_arg(valist, Object*);
        __print_object(cur);
        if (i < n - 1)
            printf("%s", sep);
    }
    va_end(valist);
    printf("%s", end);
}