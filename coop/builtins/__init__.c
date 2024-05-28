//
// Created by t-danachum on 27/05/2024.
//

#include <string.h>
#include "__init__.h"
#include "types/Integer.h"
#include "types/String.h"
#include "types/Type.h"
#include "types/Number.h"
#include "types/Function.h"
#include "types/Field.h"
#include "../object.h"
#include "../macros.h"
#include "../memory/allocator.h"
#include "functions/print.h"

Object *new_object(Object *type) {
    Object *res = acquire(sizeof(Object));
    *res = init_object(type);
    return res;
}

char *duplicate_str(const char *s) {
    char *res = acquire(strlen(s) + 1);
    strcpy(res, s);
    return res;
}

Object *new_string(const char *s) {
    Object *res = new_object(String);
    res->data = acquire(strlen(s) + 1);
    strcpy(res->data, s);
    return res;
}

void append_attr(Object *obj, Object *attr) {
    if (obj == NULL || attr == NULL) return;
    Object **new_attrs = acquire(sizeof(Object *) * (obj->num_attributes + 1));
    if (obj->attributes != NULL) {
        memcpy(new_attrs, obj->attributes, sizeof(Object *) * obj->num_attributes);
        release(obj->attributes);
    }
    obj->attributes = new_attrs;
    obj->attributes[obj->num_attributes] = attr;
    obj->num_attributes += 1;
}

Object *new_field(Object *name_field, Object *value) {
    Object *res = new_object(Field);
    append_attr(res, name_field);
    res->data = value;
    return res;
}

Object *new_integer(int n) {
    Object *res = new_object(Integer);
    res->data = acquire(sizeof(int));
    *((int *) res->data) = n;
    return res;
}


void init_builtins(void) {
    init_type();
    init_number();
    init_string();
    init_integer();
    init_function();
    init_field();

//  create diagrams/flow1.png
    Object *string__len__ = new_string(LEN);
    Object *string__len__value__len__ = new_integer(strlen(LEN));
    Object *string__name__ = new_string(NAME);
    Object *string__name__value__len__ = new_integer(strlen(NAME));

    Object *string__name__field__len__ = new_field(NULL, string__name__value__len__);
    Object *string__len__field__len__ = new_field(NULL, string__len__value__len__);
    Object *field__len__field__name__ = new_field(NULL, string__len__);
    Object *field__name__field__name__ = new_field(NULL, string__name__);

    append_attr(string__name__field__len__, field__len__field__name__);
    append_attr(string__len__field__len__, field__len__field__name__);
    append_attr(field__len__field__name__, field__name__field__name__);
    append_attr(field__name__field__name__, field__name__field__name__);

    println(string__len__);
    println(string__len__value__len__);
    println(string__name__);
    println(string__name__value__len__);

    println(string__name__field__len__);
    println(string__len__field__len__);
    println(field__len__field__name__);
    println(field__name__field__name__);
}