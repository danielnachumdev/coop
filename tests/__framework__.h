//
// Created by danie on 21/07/2024.
//

#ifndef COOP___FRAMEWORK___H
#define COOP___FRAMEWORK___H
#include "../coop/__init__.h"
extern int num_tests;
extern int passed_tests;
#define ASSERT_OBJECT_EQUALS(obj1, obj2) EXPR( \
    bool res=object_equals(obj1, obj2);        \
    passed_tests+=res;                   \
    if(not(res))                      \
        println(                         \
            __new_string(__FILE__ " at function"),   \
            __new_string(__func__),              \
            __new_string("at line"),\
            new_integer(__LINE__),       \
            __new_string("| FAILED\n\tInput1    :"),           \
            __new_string(#obj1 "\n\tInput2    :"),        \
            __new_string(#obj2),              \
            __new_string("\n\tEvaluation:"),    \
            obj1,                           \
            __new_string("=="),             \
            obj2,                           \
            __new_string("  => FALSE\n\tExpected  : TRUE\n")\
        );                               \
    num_tests+=1;                              \
    fflush(stdout);\
)
#define ASSERT_OBJECT_NOT_EQUALS(obj1, obj2) EXPR( \
    bool res=not(object_equals(obj1, obj2));        \
    passed_tests+=res;                   \
    if(not(res))                      \
        println(                         \
            __new_string(__FILE__ " at function"),   \
            __new_string(__func__),              \
            __new_string("at line"),\
            new_integer(__LINE__),       \
            __new_string("| FAILED\n\tInput1    :"),           \
            __new_string(#obj1 "\n\tInput2    :"),        \
            __new_string(#obj2),              \
            __new_string("\n\tEvaluation:"),    \
            obj1,                           \
            __new_string("!="),             \
            obj2,                           \
            __new_string("  => FALSE\n\tExpected  : TRUE\n")\
        );                               \
    num_tests+=1;                                  \
    fflush(stdout);\
)
#define ASSERT_TRUE(x) EXPR( \
    bool res=(x);        \
    passed_tests+=res;                   \
    if(not(res))                      \
        println(                         \
            __new_string(__FILE__ " at function"),   \
            __new_string(__func__),              \
            __new_string("at line"),\
            new_integer(__LINE__),       \
            __new_string("| FAILED\n\tInput     :"),           \
            __new_string(#x),                           \
            __new_string("\n\tEvaluation:"),    \
            new_boolean(x),   \
            __new_string("\n\tExpected  : true\n")\
        );                               \
    num_tests+=1;                              \
)
#define ASSERT_FALSE(x) EXPR( \
    bool res=not(x);        \
    passed_tests+=res;                   \
    if(not(res))                      \
        println(                         \
            __new_string(__FILE__ " at function"),   \
            __new_string(__func__),              \
            __new_string("at line"),\
            new_integer(__LINE__),       \
            __new_string("| FAILED\n\tInput     :"),           \
            __new_string(#x),                           \
            __new_string("\n\tEvaluation:"),    \
            new_boolean(x),   \
            __new_string("\n\tExpected  : false\n")\
        );                               \
    num_tests+=1;             \
    fflush(stdout);\
)
#define ASSERT_NULL(x) EXPR( \
    bool res=(x)==NULL;        \
    passed_tests+=res;                   \
    if(not(res))                      \
        println(                         \
            __new_string(__FILE__ " at function"),   \
            __new_string(__func__),              \
            __new_string("at line"),\
            new_integer(__LINE__),       \
            __new_string("| FAILED\n\tInput     :"),           \
            __new_string(#x),                           \
            __new_string("\n\tEvaluation:"),    \
            x,  \
            __new_string("== NULL  => FALSE\n\tExpected  : TRUE\n")\
        );                               \
    num_tests+=1;            \
    fflush(stdout);\
)
#define ASSERT_NOT_NULL(x) EXPR( \
    bool res=(x)!=NULL;        \
    passed_tests+=res;                   \
    if(not(res))                      \
        println(                         \
            __new_string(__FILE__ " at function"),   \
            __new_string(__func__),              \
            __new_string("at line"),\
            new_integer(__LINE__),       \
            __new_string("| FAILED\n\tInput     :"),           \
            __new_string(#x),                           \
            __new_string("\n\tEvaluation:"),    \
            x,  \
            __new_string("!= NULL  => FALSE\n\tExpected  : TRUE\n")\
        );                               \
    num_tests+=1;                \
    fflush(stdout);\
)
#define TEST_START(segment) printf("============== TEST '%s' STARTED ==============\n", segment)
#define TEST_END(segment) printf("============== TEST '%s' FINISHED ==============\n", segment)

#endif //COOP___FRAMEWORK___H
