//
// Created by t-danachum on 27/05/2024.
//

#include <string.h>
#include "__init__.h"
#include "../memory/allocator.h"

Attribute *__global__name__attr__ = NULL;
Attribute *__global__len__attr__ = NULL;

void init_types(void) {
    //    THE ORDER MATTERS!
    __init_type();
    __init_number();
    __init_string();
    __init_integer();
    __init_function();
    __init_array();
    __init_boolean();
    __init_union();
}

void flow1(void) {
    __global__name__attr__ = acquire(sizeof(Attribute));
    __global__name__attr__->key = NAME;
    __global__name__attr__->value = new_object(String);
    __global__name__attr__->value->data = NAME;
    __global__name__attr__->value->num_attributes = 1;
    __global__name__attr__->value->attributes = acquire(sizeof(Attribute));
    __global__name__attr__->value->attributes[0] = *__global__name__attr__;

    __global__len__attr__ = acquire(sizeof(Attribute));
    __global__len__attr__->key = LEN;
    __global__len__attr__->value = new_object(String);
    __global__len__attr__->value->data = LEN;
    __global__len__attr__->value->num_attributes = 1;
    __global__len__attr__->value->attributes = acquire(sizeof(Attribute));
    __global__len__attr__->value->attributes[0] = *__global__name__attr__;
}

void init_builtins(void) {
    init_types();
    flow1();
//    setattr(Type, NAME, new__name__field("Type"));
//    setattr(String, NAME, new__name__field("String"));
//    setattr(Number, NAME, new__name__field("Number"));
//    setattr(Integer, NAME, new__name__field("Integer"));
//    setattr(Function, NAME, new__name__field("Function"));
//    setattr(Field, NAME, new__name__field("Field"));
//    setattr(Array, NAME, new__name__field("Array"));
//    setattr(Boolean, NAME, new__name__field("Boolean"));
//    setattr(Union, NAME, new__name__field("Union"));
}