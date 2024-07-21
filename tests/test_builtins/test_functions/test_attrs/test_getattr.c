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

    assert_objects_equal(getattr(obj, LEN)->data, length);

    builtin_free(length_field->attributes);
    builtin_free(obj->attributes);

    assert_objects_equal(getattr(__global__field__name__field__name__, NAME),
                         __global__field__name__field__name__);
    assert_objects_equal(getattr(__global__field__len__field__name__, NAME), __global__field__name__field__name__);
    assert_objects_equal(getattr(__global__field__name__field__name__, NAME),
                             getattr(__global__field__len__field__name__, NAME));

}