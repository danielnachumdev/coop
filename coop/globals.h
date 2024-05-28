//
// Created by danie on 28/05/2024.
//

#ifndef COOP_GLOBALS_H
#define COOP_GLOBALS_H

#include "object.h"
#include "macros.h"
#include "memory/allocator.h"
#include "log/logger.h"
#include "builtins/types/Type.h"
#include "builtins/types/Field.h"
#include "builtins/types/Function.h"
#include "builtins/types/Integer.h"
#include "builtins/types/String.h"
#include "builtins/types/Number.h"
#include "builtins/functions/print.h"
#include "builtins/functions/throw.h"
#include "builtins/functions/attr/getattr.h"
#include "builtins/functions/attr/setattr.h"
#include "builtins/functions/attr/hasattr.h"

extern Object *__global__field__name__field__name__;


#endif //COOP_GLOBALS_H
