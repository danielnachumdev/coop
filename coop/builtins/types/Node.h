//
// Created by danie on 25/07/2024.
//

#ifndef COOP_NODE_H
#define COOP_NODE_H

#include "../object.h"
#include "../functions/len.h"
#include "../macros.h"

void __init_node(void);

DECLARE(Node, __init__, Object*, Object *data, Object *next, Object *prev);

#endif //COOP_NODE_H
