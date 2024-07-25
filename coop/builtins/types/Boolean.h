//
// Created by danie on 28/05/2024.
//

#ifndef COOP_BOOLEAN_H
#define COOP_BOOLEAN_H


#include "../object.h"
#include "../macros.h"

void __init_boolean(void);

DECLARE(Boolean, __init__, Object *, const bool v);

DECLARE(Boolean, __eq__, bool, const Object *, const Object *);

DECLARE(Boolean, __print__, void, const Object *);

DECLARE(Boolean, __int__, Object *, const Object *);

DECLARE(Boolean, __bool__, Object *, const Object *);

#endif //COOP_BOOLEAN_H
