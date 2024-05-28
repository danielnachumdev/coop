//
// Created by danie on 28/05/2024.
//

#ifndef COOP_PRINT_H
#define COOP_PRINT_H

#include "../../object.h"

void print_object(const Object *obj, const char *end);

#define print(obj) print_object(obj,"")
#define println(obj) print_object(obj,"\n")
#endif //COOP_PRINT_H
