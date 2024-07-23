//
// Created by danie on 24/07/2024.
//

#ifndef COOP_INIT_H
#define COOP_INIT_H

#include "../object.h"

Object *__init_helper(const Object *T, Object *instance);

#define init(type, prototype, ...) __init_helper(type, cast(getattr(type, "__init__")->data, prototype)(__VA_ARGS__))
#endif //COOP_INIT_H
