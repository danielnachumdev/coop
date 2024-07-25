//
// Created by danie on 02/06/2024.
//

#ifndef COOP_DIR_H
#define COOP_DIR_H

#include "../object.h"
#include "../../backend/linked_list.h"

void _dir(const Object *obj, int max_recursion_depth, int current_depth, char *prev_print_prefix, LinkedList *ll);

#define dir(obj) _dir(obj, 0, 0, NULL, NULL)
#endif //COOP_DIR_H
