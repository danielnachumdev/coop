//
// Created by danie on 21/07/2024.
//

#include "test_getattr.h"
#include "../../../__framework__.h"

void test_getattr(void) {
//    Object *length = new_integer(6);
//    Object *length_field = new_object(Field);
//    length_field->data = length;
//    length_field->num_attributes = 1;
//    length_field->attributes = builtin_new(sizeof(Object *));
//    length_field->attributes[0] = new_attr(NAME, __global__len__attr__);
//    Object *obj = new_object(String);
//    obj->data = "Daniel";
//    obj->num_attributes = 1;
//    obj->attributes = builtin_new(sizeof(Object *));
//    obj->attributes[0] = new_attr(LEN, length_field);
//
//    ASSERT_OBJECT_EQUALS(getattr(obj, LEN)->data, length);
//
//    builtin_free(length_field->attributes);
//    builtin_free(obj->attributes);

    ASSERT_NULL(getattr(__global__name__attr__->value, "asfjhbaslkjgfbalskbgag"));
    ASSERT_NULL(getattr(__global__name__attr__->value, "asfjhbaslkjgfbalskbgag", NULL));
    ASSERT_NOT_NULL(getattr(__global__name__attr__->value, "asfjhbaslkjgfbalskbgag", new_boolean(true)));
    ASSERT_OBJECT_EQUALS(
            getattr(__global__name__attr__->value, "asfjhbaslkjgfbalskbgag", new_string("hashdjbasjhdjbasd")),
            new_string("hashdjbasjhdjbasd"));
    ASSERT_TRUE(hasattr(__global__name__attr__->value, NAME));
    ASSERT_TRUE(hasattr(__global__name__attr__->value, LEN));
    ASSERT_TRUE(hasattr(__global__len__attr__->value, NAME));
    ASSERT_TRUE(hasattr(__global__len__attr__->value, LEN));
//    ASSERT_TRUE(__global__name__attr__->type == Field);
    ASSERT_OBJECT_EQUALS(getattr(__global__name__attr__->value, NAME),
                         __global__name__attr__->value);
    ASSERT_OBJECT_EQUALS(getattr(__global__len__attr__->value, NAME), __global__name__attr__->value);
    ASSERT_OBJECT_EQUALS(getattr(__global__name__attr__->value, NAME),
                         getattr(__global__len__attr__->value, NAME));
    ASSERT_OBJECT_NOT_EQUALS(getattr(__global__name__attr__->value, LEN),
                             getattr(__global__len__attr__->value, LEN));
}