//
// Created by danie on 18/05/2024.
//

#ifndef COOP_BUILTINS_H
#define COOP_BUILTINS_H

#include "object.h"

extern Object *Type;
extern Object *Integer;
extern Object *String;
extern Object *Array;
extern Object *Field;
extern Object *Function;


typedef struct FieldData {
    const Object *type;
    void *value;
} FieldData;

#endif //COOP_BUILTINS_H

