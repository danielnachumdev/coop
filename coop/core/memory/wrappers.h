//
// Created by danie on 17/05/2024.
//

#ifndef MACROPYTHON_BUILTINS_H
#define MACROPYTHON_BUILTINS_H

#include <malloc.h>

#define builtin_free(ptr) free(ptr)
#define builtin_new(ptr) malloc(ptr)
#endif //MACROPYTHON_BUILTINS_H
