//
// Created by danie on 26/07/2024.
//

#ifndef COOP_INPUT_H
#define COOP_INPUT_H

#include "../../object.h"
#include "../../types/String.h"

Object *input(const Object *);

#define strinput(s) input(explicitgetfunc(String,__init__)(s))

#endif //COOP_INPUT_H
