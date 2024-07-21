//
// Created by danie on 28/05/2024.
//

#ifndef COOP_TEST_H
#define COOP_TEST_H

#include "../builtins/object.h"

bool assert_objects_equal(const Object *obj1, const Object *obj2);

bool assert_objects_not_equal(const Object *obj1, const Object *obj2);

bool assert_true(bool x);

bool assert_false(bool x);

bool assert_null(const Object *obj);

bool assert_not_null(const Object *obj);

void test_start(const char *segment_name);

void test_end(const char *segment_name);

#endif //COOP_TEST_H
