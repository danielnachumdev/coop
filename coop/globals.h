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
#include "builtins/types/Array.h"
#include "builtins/functions/print.h"
#include "builtins/functions/throw.h"
#include "builtins/functions/attr/getattr.h"
#include "builtins/functions/attr/setattr.h"
#include "builtins/functions/attr/hasattr.h"

#define NAME "__name__"
#define INIT "__init__"
#define LEN "__len__"
#define RETURN_TYPE "__return_type__"
#define COPY "__copy__"
#define cast(obj, T) ((T)obj)


extern Object *__global__field__name__field__name__;
extern Object *__global__field__len__field__name__;

bool isinstance(const Object* obj, const Object * T);



#endif //COOP_GLOBALS_H
