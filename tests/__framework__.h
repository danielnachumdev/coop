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
            new_string(__FILE__ " at function"),   \
            new_string(__func__),              \
            new_string("at line"),\
            new_integer(__LINE__),       \
            new_string("| FAILED\n\tInput1    :"),           \
            new_string(#obj1 "\n\tInput2    :"),        \
            new_string(#obj2),              \
            new_string("\n\tEvaluation:"),    \
            obj1,                           \
            new_string("=="),             \
            obj2,                           \
            new_string("  => FALSE\n\tExpected  : TRUE\n")\
        );                               \
    num_tests+=1;                              \
)
#define ASSERT_OBJECT_NOT_EQUALS(obj1, obj2) EXPR( \
    bool res=not(object_equals(obj1, obj2));        \
    passed_tests+=res;                   \
    if(not(res))                      \
        println(                         \
            new_string(__FILE__ " at function"),   \
            new_string(__func__),              \
            new_string("at line"),\
            new_integer(__LINE__),       \
            new_string("| FAILED\n\tInput1    :"),           \
            new_string(#obj1 "\n\tInput2    :"),        \
            new_string(#obj2),              \
            new_string("\n\tEvaluation:"),    \
            obj1,                           \
            new_string("!="),             \
            obj2,                           \
            new_string("  => FALSE\n\tExpected  : TRUE\n")\
        );                               \
    num_tests+=1;                              \
)
#define ASSERT_TRUE(x) EXPR( \
    bool res=(x);        \
    passed_tests+=res;                   \
    if(not(res))                      \
        println(                         \
            new_string(__FILE__ " at function"),   \
            new_string(__func__),              \
            new_string("at line"),\
            new_integer(__LINE__),       \
            new_string("| FAILED\n\tInput     :"),           \
            new_string(#x),                           \
            new_string("\n\tEvaluation:"),    \
            new_boolean(x),   \
            new_string("\n\tExpected  : true")\
        );                               \
    num_tests+=1;                              \
)
#define ASSERT_FALSE(x) EXPR( \
    bool res=not(x);        \
    passed_tests+=res;                   \
    if(not(res))                      \
        println(                         \
            new_string(__FILE__ " at function"),   \
            new_string(__func__),              \
            new_string("at line"),\
            new_integer(__LINE__),       \
            new_string("| FAILED\n\tInput     :"),           \
            new_string(#x),                           \
            new_string("\n\tEvaluation:"),    \
            new_boolean(x),   \
            new_string("\n\tExpected  : false")\
        );                               \
    num_tests+=1;                              \
)
#define ASSERT_NULL(x) ASSERT_TRUE((x) == NULL)
#define ASSERT_NOT_NULL(x) ASSERT_TRUE((x) != NULL)
#define TEST_START(segment) printf("============== TEST '%s' STARTED ==============\n", segment)
#define TEST_END(segment) printf("============== TEST '%s' FINISHED ==============\n", segment)

#endif //COOP___FRAMEWORK___H
