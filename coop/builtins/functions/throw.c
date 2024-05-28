//
// Created by danie on 28/05/2024.
//

#include <stdbool.h>
#include "throw.h"
#include "../../memory/allocator.h"

void print_stack(const Exception *e) {
    const Exception *cur = e;
    bool first_flag = true;
    while (cur != NULL) {
        if (first_flag) {
            fprintf(stderr, "%s at line number %lu: %s(%s)\n", cur->filename, cur->line_number, cur->name, cur->msg);
            first_flag = false;
        } else {
            fprintf(
                    stderr,
                    "\tfrom %s at line number %lu: %s(%s)\n",
                    cur->filename, cur->line_number, cur->name, cur->msg
            );
        }
        cur = cur->parent;
    }
}

void throw_impl(const Exception *e) {
    if (e != NULL)
        print_stack(e);
    get_allocator()->clear();
    exit(e != NULL ? e->exit_code : 1);
}