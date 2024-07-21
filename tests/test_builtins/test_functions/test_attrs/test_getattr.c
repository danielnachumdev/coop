//
// Created by danie on 21/07/2024.
//

#include "test_getattr.h"
#include "../../../../coop/__init__.h"

void test_getattr(void) {
    Object *length = new_integer(6);
    Object *length_field = new_object(Field);
    length_field->data = length;
    length_field->num_attributes = 1;
    length_field->attributes = builtin_new(sizeof(Object *));
    length_field->attributes[0] = __global__field__len__field__name__;
    Object *obj = new_object(String);
    obj->data = "Daniel";
    obj->num_attributes = 1;
    obj->attributes = builtin_new(sizeof(Object *));
    obj->attributes[0] = length_field;

    ASSERT_OBJECT_EQUALS(getattr(obj, LEN)->data, length);

    builtin_free(length_field->attributes);
    builtin_free(obj->attributes);

    ASSERT_NULL(getattr(__global__field__name__field__name__, "asfjhbaslkjgfbalskbgag"));
    ASSERT_NULL(getattr(__global__field__name__field__name__, "asfjhbaslkjgfbalskbgag", NULL));
    ASSERT_NOT_NULL(getattr(__global__field__name__field__name__, "asfjhbaslkjgfbalskbgag", new_boolean(true)));
    ASSERT_OBJECT_EQUALS(getattr(__global__field__name__field__name__, "asfjhbaslkjgfbalskbgag", new_string("hashdjbasjhdjbasd")),
                         new_string("hashdjbasjhdjbasd"));
    ASSERT_NOT_NULL(getattr(__global__field__name__field__name__, NAME));
    ASSERT_NOT_NULL(getattr(__global__field__name__field__name__, LEN));
    ASSERT_NOT_NULL(getattr(__global__field__len__field__name__, NAME));
    ASSERT_NOT_NULL(getattr(__global__field__len__field__name__, LEN));
    ASSERT_TRUE(__global__field__name__field__name__->type == Field);
    ASSERT_OBJECT_EQUALS(getattr(__global__field__name__field__name__, NAME),
                         __global__field__name__field__name__);
    ASSERT_OBJECT_EQUALS(getattr(__global__field__len__field__name__, NAME), __global__field__name__field__name__);
    ASSERT_OBJECT_EQUALS(getattr(__global__field__name__field__name__, NAME),
                         getattr(__global__field__len__field__name__, NAME));
    ASSERT_OBJECT_NOT_EQUALS(getattr(__global__field__name__field__name__, LEN),
                             getattr(__global__field__len__field__name__, LEN));
}