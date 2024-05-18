//
// Created by danie on 18/05/2024.
//

#ifndef MACROPYTHON_OBJECT_H
#define MACROPYTHON_OBJECT_H

#include "type.h"
#include "field.h"
#include "function.h"

typedef struct Object {
    Type *type;
    unsigned int num_fields;
    Field **fields;
    unsigned int num_functions;
    Function **functions;
} Object;
#endif //MACROPYTHON_OBJECT_H
