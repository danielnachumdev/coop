//
// Created by t-danachum on 21/05/2024.
//

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "_main.h"
#include "coop/log/logger.h"
#include "coop/memory/allocator.h"
#include "coop/object.h"
#include "coop/macros.h"


Object *getattr(const Object *obj, const char *name) {
    _DEBUG("Entered 'getattr'\n");
    if (obj == NULL || name == NULL) return NULL;
    for (unsigned int i = 0; i < obj->num_attributes; ++i) {
        Object *attr = obj->attributes[i];
        for (unsigned int j = 0; j < attr->num_attributes; ++j) {

        }
    }
    return NULL;
}


void setattr_helper_case_null(Object *obj, const char *name, const Object *value) {
    Object *(*dup_func)(const Object *) = getattr(value, COPY);
    if (dup_func == NULL) return;
    Object *duplication = dup_func(value);
    Object **new_attributes = acquire(sizeof(Object *) * (obj->num_attributes + 1));
    memcpy(new_attributes, obj->attributes, obj->num_attributes * sizeof(Object *));
    new_attributes[obj->num_attributes] = duplication;
    obj->attributes = new_attributes;
    obj->num_attributes += 1;
}

void setattr_helper_case_not_null(Object *obj, const char *name, const Object *value) {

}

void setattr(Object *obj, const char *name, const Object *value) {
    _DEBUG("Entered 'setattr'\n");
    Object *attr = getattr(obj, name);
    if (attr == NULL) {
        setattr_helper_case_null(obj, name, value);
        return;
    }
    setattr_helper_case_not_null(obj, name, value);
}

bool hasattr(Object *obj, const char *name) {
    _DEBUG("Entered 'hasattr'\n");
    return getattr(obj, name) != NULL;
}

char *duplicate_str(const char *s) {
    char *res = acquire(strlen(s) + 1);
    strcpy(res, s);
    return res;
}

Object *basic_new_string(const char *s) {
    Object *res = acquire(sizeof(Object));
    *res = init_object(String);
    res->data = acquire(strlen(s) + 1);
    strcpy(res->data, s);
    return res;
}

void _main(void) {
    Object *the_string___name__object = basic_new_string(NAME);
    Object *the_string___length__object = basic_new_string(LENGTH);


    Object *the_string___copy__object = basic_new_string(COPY);

    Object *String_copy_func = acquire(sizeof(Object));
    *String_copy_func = init_object(Function);
    String_copy_func->data = duplicate_str;
    String_copy_func->num_attributes = 1;
    String_copy_func->attributes = acquire(sizeof(Object *) * 1);

    Object *the_string_String_object = basic_new_string("String");


    setattr(String, NAME, the_string_String_object);
}