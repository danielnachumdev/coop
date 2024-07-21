//
// Created by t-danachum on 27/05/2024.
//

#ifndef COOP_BUILTINS___INIT___H
#define COOP_BUILTINS___INIT___H

#include "types/__init__.h"
#include "functions/__init__.h"
#include "exception.h"
#include "constants.h"
#include "macros.h"
#include "object.h"

extern Attribute *__global__name__attr__;
extern Attribute *__global__len__attr__;

void init_builtins(void);


#endif //COOP_BUILTINS___INIT___H
