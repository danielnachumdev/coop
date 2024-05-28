//
// Created by danie on 28/05/2024.
//

#include <stdio.h>
#include <stdarg.h>
#include "print.h"
#include "../../globals.h"

void print_object(Object *obj) {
    if (obj == NULL) {
        printf("NULL");
        return;
    }
    if (obj->type == Type) {
        printf("Type(name=");
        print_object(getattr(obj, NAME));
        printf(")");
    } else if (obj->type == Array) {
        printf("[");
        Object *array_length = getattr(obj, LEN);
        if (array_length != NULL)
            print_object(array_get(obj, 0));
        for (unsigned int i = 1; i < *cast(array_length->data, unsigned int *); ++i) {
            printf(", ");
            print_object(array_get(obj, i));
        }
        printf("]");
    } else if (obj->type == Number) {
        printf("Type(Subtype=Number, name=");
        print_object(getattr(obj, NAME));
        printf(")");
    } else if (obj->type == Boolean)
        printf("%s", *cast(obj->data, bool *) ? "true" : "false");
    else if (obj->type == Integer)
        printf("%lu", *cast(obj->data, unsigned long *));
    else if (obj->type == String)
        printf("%s", cast(obj->data, char *));
    else if (obj->type == Field) {
        printf("Field(name=");
        print_object(getattr(obj, NAME));
        printf(", data=");
        print_object(obj->data);
        printf(")");
    }
}


void print_imp(const char *sep, const char *end, unsigned int n, ...) {
    if (sep == NULL || end == NULL) return;
    va_list valist;
    va_start(valist, n);
    for (unsigned int i = 0; i < n; ++i) {
        Object *cur = va_arg(valist, Object*);
        print_object(cur);
        printf("%s", sep);
    }
    va_end(valist);
    printf("%s", end);
}