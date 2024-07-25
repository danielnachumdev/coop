//
// Created by danie on 25/07/2024.
//

#ifndef COOP_SUPER_H
#define COOP_SUPER_H

#include "../object.h"
#include "../types/Integer.h"

Object *super(const Object *self, IntegerT steps);

#define superfunc(obj,steps,name,prototype) cast(getattr(super(obj,steps),name)->data,prototype)

#endif //COOP_SUPER_H
