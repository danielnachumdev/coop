//
// Created by danie on 19/05/2024.
//

#ifndef COOP_GLOBALS_H
#define COOP_GLOBALS_H

#include <stdbool.h>
#include "builtins.h"

Object *get(Object *obj, const char *key);

bool contains(const Object *obj, const char *key);

Object *set(Object *obj, const char *key, Object *value);

void dir(const Object *obj);

#endif //COOP_GLOBALS_H
