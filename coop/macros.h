//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_MACROS_H
#define LOCAL_PLAYGROUND_MACROS_H

#include <malloc.h>

#define builtin_new(x) malloc(x)
#define builtin_free(x) free(x)


#define EXPAND(x) x
#define PASTE2(a, b) a ## b
#define PASTE3(a, b, c) a ## b ## c
#define STRINGIFY(x) #x
#define STR(x) STRINGIFY(x)
#define NUM_ARGS(T, filler_item_of_type_T, ...) (sizeof((T[]){filler_item_of_type_T, ##__VA_ARGS__})/sizeof(T)-1)
#define NUM_POINTERS(...) NUM_ARGS(const void *, NULL, __VA_ARGS__)
#define __IMPL_IS_EMPTY_RES(x) (x == 0)
#define IS_EMPTY(x) PASTE2(__IMPL_, IS_EMPTY_RES(NUM_POINTERS(x)))
#define CAST(obj, T) (T)obj
#define ISINSTANCE(x, T) _Generic(x,    \
        T: true,                        \
        default: false                  \
    )
#define EXPR(expr) do{ expr } while(0)
#define RETURN_DO_IF(condition, scoped_actions) EXPR( if (condition){ {scoped_actions} return;})
#define RETURN_VALUE_DO_IF(condition, scoped_actions, value) EXPR( if (condition){ {scoped_actions} return value;})
#define COUNTER() __COUNTER__
#define LOOP_VA_ARGS(name, T, N) \
    T* name = acquire(sizeof(T)).nullable; \
    EXPR(                                                                   \
        for (unsigned int i = 0; i < N; i++) \
            name[i] = va_arg(valist, T);\
    )                                                                        \



#define DEFER_FREE(name, allocated, body) EXPR( \
    Object * name=allocated;                  \
    {                                         \
    body\
    }                                         \
    release(name);\
)

#define BREAKABLE(body) EXPR(body)


#endif //LOCAL_PLAYGROUND_MACROS_H
