//
// Created by danie on 28/05/2024.
//

#ifndef COOP_TEST_H
#define COOP_TEST_H
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
            new_string("| FAILED\n\tExpected:"),           \
            new_string(#obj1 " =="),        \
            new_string(#obj2),              \
            new_string("\n\tGot     :"),    \
            obj1,                           \
            new_string("=="),             \
            obj2,                           \
            new_string("  => FALSE\n")\
        );                               \
    num_tests+=1;                              \
)
#define ASSERT_TRUE(x) ASSERT_OBJECT_EQUALS(new_boolean(x), new_boolean(true))
#define ASSERT_FALSE(x) ASSERT_TRUE(not(x))
#define ASSERT_NULL(x) ASSERT_TRUE((x) == NULL)
#define ASSERT_NOT_NULL(x) ASSERT_TRUE((x) != NULL)
#endif //COOP_TEST_H
