//
// Created by danie on 21/07/2024.
//

#include "test_getattr.h"
#include "../../../__framework__.h"

#define MISSING "asfjhbaslkjgfbalskbgag"
#define REPLACE "hashdjbasjhdjbasd"

void test_getattr(void) {
    ASSERT_TRUE(hasattr(String, "__init__"));
    ASSERT_TRUE(hasattr(String, "__eq__"));
    ASSERT_TRUE(hasattr(String, "__print__"));
    ASSERT_TRUE(hasattr(String, "__bool__"));
    ASSERT_FALSE(hasattr(String, "dfskjbnlsdkfjnh"));
    ASSERT_FALSE(hasattr(implicitgetfunc(String,__init__)("asdasd"), "dfskjbnlsdkfjnh"));
    ASSERT_TRUE(hasattr(implicitgetfunc(String,__init__)("asdasd"), "__print__"));
}