//
// Created by danie on 28/05/2024.
//

#ifndef COOP_GETATTR_H
#define COOP_GETATTR_H

#include "../../object.h"
#include "../../macros.h"

Object *_getattr(const Object *obj, const char *key, unsigned int num_args, ...);

#define getattr(obj, key, ...) _getattr(obj,key,NUM_POINTERS(__VA_ARGS__),##__VA_ARGS__)
#endif //COOP_GETATTR_H
