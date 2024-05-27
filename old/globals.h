//
// Created by danie on 19/05/2024.
//

#ifndef COOP_GLOBALS_H
#define COOP_GLOBALS_H

#include <stdbool.h>
#include "builtins.h"

Object *getattr(Object *obj, const char *key);

bool hasattr(const Object *obj, const char *key);

Object *setattr(Object *obj, const char *key, Object *value);

void dir(const Object *obj);

#endif //COOP_GLOBALS_H
