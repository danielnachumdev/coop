//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_MACROS_H
#define LOCAL_PLAYGROUND_MACROS_H

#include <malloc.h>
#include <stdio.h>
#include "wrappers.h"

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
#define PASS EXPR(int _ =0;)
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


#define cast(obj, T) ((T)obj)
#define not(exp) !(exp)
#define __FUNCTION_POINTER_BUILDER(name, ret, get, ...) ret(*name)(get,##__VA_ARGS__)
#define Runnable(name) __FUNCTION_POINTER_BUILDER(name,void,void)
#define Supplier(name) __FUNCTION_POINTER_BUILDER(name,void*,void)
#define Supplier_CONST(name) __FUNCTION_POINTER_BUILDER(name,const void*,void)
#define ConsumerT(name) __FUNCTION_POINTER_BUILDER(name,void,void*)
#define Consumer_CONST(name) __FUNCTION_POINTER_BUILDER(name,void,const void*)
#define Transformation(name) __FUNCTION_POINTER_BUILDER(name,void*,void*)
#define Transformation_CONST(name) __FUNCTION_POINTER_BUILDER(name,void*,const void*)
#define DuplicatorT(name) Transformation_CONST(name)


#define builtin_new(n) builtin_new_wrapper_impl(n,__FILE_NAME__,__LINE__)
#define builtin_free(p) printf("%-15s at line %4u: Pointer = %p\n",__FILE_NAME__,__LINE__,p); fflush(stdout); free(p)

#endif //LOCAL_PLAYGROUND_MACROS_H
