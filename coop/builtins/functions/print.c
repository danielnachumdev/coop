//
// Created by danie on 28/05/2024.
//

#include <stdio.h>
#include "print.h"
#include "../../macros.h"
#include "getattr.h"

void print_object(const Object *obj, const char *end) {
    if (obj == NULL) {
        printf("NULL%s", end);
        return;
    }
    if (obj->type == Integer) {
//        printf("Integer(%d)%s", *((const int *) obj->data), end);
        printf("%d%s", *((const int *) obj->data), end);
    } else if (obj->type == String) {
//        printf("String(\"%s\")%s", ((const char *) obj->data), end);
        printf("\"%s\"%s", ((const char *) obj->data), end);
    } else if (obj->type == Field) {
        printf("Field(name=");
        print(getattr(obj, NAME));
        printf(", data=");
        print(obj->data);
        printf(")%s", end);
    }
}
