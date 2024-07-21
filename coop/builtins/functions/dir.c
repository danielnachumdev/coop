
//
// Created by danie on 02/06/2024.
//

#include <string.h>
#include "dir.h"
#include "../constants.h"
#include "attr/getattr.h"
#include "print.h"
#include "../../memory/__init__.h"

void
_dir(const Object *obj, bool recursive, char *prev_print_prefix, const Object ***visited, int *visited_length_ptr) {
    if (obj == NULL) return;
    if (prev_print_prefix == NULL) prev_print_prefix = "";
    int current_length = (int) strlen(prev_print_prefix);
    char *current_print_prefix = acquire(sizeof(char) * (current_length + 2));
    strcpy(current_print_prefix, prev_print_prefix);
    current_print_prefix[current_length] = '\t';
    current_print_prefix[current_length + 1] = '\0';
    if (visited == NULL && recursive) {
        visited = acquire(sizeof(Object ***));
        if (visited == NULL) return;
        *visited = acquire(sizeof(Object **));
        if (*visited == NULL) return;
        if (visited_length_ptr == NULL)
            visited_length_ptr = acquire(sizeof(int));
        if (visited_length_ptr == NULL) return;
        *visited_length_ptr = 1;
        (*visited)[0] = obj;
    } else if (visited != NULL && visited_length_ptr != NULL) {
        for (int i = 0; i < *visited_length_ptr; ++i)
            if (obj == (*visited)[i]) {
                printf("%sObject at %p (...)\n", current_print_prefix, obj);
                return;
            }
        const Object **new_visited = acquire(sizeof(Object *) * (*visited_length_ptr + 1));
        memcpy(new_visited, visited, *visited_length_ptr * sizeof(Object *));
        new_visited[*visited_length_ptr] = obj;
        *visited_length_ptr += 1;
        *visited = new_visited;
    }

    printf("%sObject ( // %p\n", prev_print_prefix, obj);
    printf("%stype: %s // %p\n", current_print_prefix, (char *) getattr(obj->type, NAME)->data, obj->type);

    printf("%sAttributes: [", current_print_prefix);
    if (obj->num_attributes > 0)
        printf(" // length = %lu\n", obj->num_attributes);
    for (int i = 0; i < obj->num_attributes; ++i) {
        Attribute *attr = obj->attributes + i;
        if (recursive) _dir(attr->value, true, current_print_prefix, visited, visited_length_ptr);
        else {
            printf("%s\t", current_print_prefix);
            printf("%s", (char *) getattr(attr->value, NAME)->data);
            print(attr);
            printf("\n");
        }
    }
    if (obj->num_attributes > 0)
        printf("%s", current_print_prefix);
    printf("]\n");
    printf(")\n");
}