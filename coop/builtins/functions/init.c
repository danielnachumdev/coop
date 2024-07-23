//
// Created by danie on 24/07/2024.
//
#include "init.h"


Object *__init_helper(const Object *T, Object *instance) {
    instance->type = T;
    return instance;
}