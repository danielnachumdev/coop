//
// Created by danie on 02/06/2024.
//

#ifndef COOP_DIR_H
#define COOP_DIR_H

#include "../object.h"

void _dir(const Object *obj, bool recursive, char *prev_print_prefix, const Object ***visited, int *visited_length_ptr);

#define dir(obj, recursive) _dir(obj,recursive,NULL,NULL,NULL)
#endif //COOP_DIR_H
