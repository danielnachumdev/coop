//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_MACROS_H
#define LOCAL_PLAYGROUND_MACROS_H

#include <malloc.h>

#define builtin_new(x) malloc(x)
#define builtin_free(x) free(x)

#define NAME "__name__"
#define INIT "__init__"
#define LENGTH "__length__"
#define COPY "__copy__"

#endif //LOCAL_PLAYGROUND_MACROS_H
