
//
// Created by danie on 02/06/2024.
//

#include <string.h>
#include "dir.h"
#include "attr/getattr.h"
#include "print.h"
#include "../../memory/__init__.h"

void *dup_func(const void *p) {
    return (void *) p;
}

void free_func(void *p) {}

void
print_attrs(const Object *obj, bool recursive, int current_depth, char *prev_print_prefix, char *current_print_prefix,
            LinkedList *ll) {
    printf("%s\tAttributes: [", prev_print_prefix);
    if (obj->num_attributes > 0)
        printf(" // length = %lu\n", obj->num_attributes);
    for (int i = 0; i < obj->num_attributes; ++i) {
        Attribute *attr = obj->attributes[i];
        if (attr == NULL) {
            printf("%s\t\tNULL: \n", prev_print_prefix);
            continue;
        }
        if (recursive) {
            printf("%s\t\t'%s': ", prev_print_prefix, (char *) attr->key);
            _dir(attr->value, true, current_depth + 1, current_print_prefix, ll);
        } else {
            printf("%s\t\t", prev_print_prefix);
            printf("'%s': ", (char *) attr->key);
            print(attr->value);
            printf("\n");
        }
    }
    if (obj->num_attributes > 0)
        printf("%s\t", prev_print_prefix);
    printf("]\n");
}

void _dir(const Object *obj, bool recursive, int current_depth, char *prev_print_prefix, LinkedList *ll) {
    if (obj == NULL) return;
    if (prev_print_prefix == NULL) prev_print_prefix = "";
    int current_length = (int) strlen(prev_print_prefix);
    char *current_print_prefix = acquire(sizeof(char) * (current_length + 2));
    strcpy(current_print_prefix, prev_print_prefix);
    current_print_prefix[current_length] = '\t';
    current_print_prefix[current_length + 1] = '\t';
    current_print_prefix[current_length + 2] = '\0';
    if (recursive) {
        if (ll == NULL) {
            ll = linkedlist_new(dup_func, free_func, (bool(*)(const void *, const void *)) object_equals);
            linkedlist_add(ll, (void *) obj);
        } else {
            if (linkedlist_contains(ll, obj)) {
                printf("Object (...) // %p\n", obj);
                return;
            }
            linkedlist_add(ll, (void *) obj);
        }
    }

    printf("Object ( // %p\n", obj);
    printf("%s\ttype: %s // %p\n", prev_print_prefix, (char *) getattr(obj->type, "__name__")->data, obj->type);
    printf("%s\tdata: ", prev_print_prefix);
    println(obj);
    print_attrs(obj, recursive, current_length, prev_print_prefix, current_print_prefix, ll);
    printf("%s)\n", prev_print_prefix);
    if (current_depth == 0)
        linkedlist_free(&ll);
}