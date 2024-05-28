//
// Created by danie on 28/05/2024.
//

#ifndef COOP_ARRAY_H
#define COOP_ARRAY_H

#include "../../globals.h"

void __init_array(void);

Object *new_array(unsigned int num_objects, Object *items_type);

#endif //COOP_ARRAY_H
