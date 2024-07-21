//
// Created by danie on 21/07/2024.
//

#include "test_isinstance.h"
#include "../../../coop/__init__.h"

void test_isinstance(void) {
    assert_true(isinstance(Integer, Number));
    assert_true(isinstance(Number, Type));
    assert_true(isinstance(Integer, Type));
    Object *Attr = new_union(2, Field, Function);
    assert_true(isinstance(Field, Attr));
    assert_true(isinstance(Function, Attr));
    assert_true(isinstance(__global__field__name__field__name__, Field));
    assert_true(isinstance(__global__field__name__field__name__, Attr));
    assert_true(isinstance(new_string(""), String));
    assert_true(isinstance(new_integer(1), Integer));
    assert_false(isinstance(new_integer(1), String));
}