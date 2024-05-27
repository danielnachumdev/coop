//
// Created by danie on 17/05/2024.
//
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "coop/builtins.h"
#include "coop/print.h"
#include "coop/core/macros.h"
#include "coop/core/memory//allocator.h"
#include "coop/core/logging/logger.h"
#include "coop/duplicators.h"
#include "coop/globals.h"

#define F(x) STR(x)," => ", x

#define init_object(type_, num_, data_) (Object){ \
    .type=type_,\
    .num_attributes=num_,\
    .attributes=new_object_ptr(num_),\
    .data=data_          \
}
#define init_fielddata(type_, value_) (FieldData) {\
            .type=type_,\
            .value=value_\
    }
#define set_attr(obj, index, f) (obj)->attributes[index]=f
#define get_attr(obj, index) (obj)->attributes[index]
#define declare_object(name) Object * name = new_object(1)
#define declare_fd(name) FieldData* name = acquire(sizeof(FieldData)).nullable

Object *new_field_instance(
        const char *name,
        const Object *type,
        const void *value,
        void *(dup)(const void *),
        Object *parent
);

Object *new_string_instance(
        const char *s,
        Object *parent
);

Object *new_function_instance(
        void *(*impl)(),
        const char *name,
        Object *parent
);

#define new_field(name, type, value, dup) new_field_instance(name,type,value,(void *(*)(const void *))dup,NULL)
#define new_string(s) new_string_instance(s,NULL)
#define new_function(impl, name) new_function_instance((void *(*)())impl,name,NULL)

Object *new_string_instance(
        const char *s,
        Object *parent
) {
    declare_object(res);
    *res = init_object(String, 0, duplicate_string(s));
    return res;
}

Object *
new_field_instance(
        const char *name,
        const Object *type,
        const void *value,
        void *(*dup)(const void *),
        Object *parent
) {
    Object *res = acquire(sizeof(Object)).nullable;
    res->type = Field;
    res->attributes = acquire(sizeof(*res->attributes) * 2).nullable;
    res->num_attributes = 2;

    // create sub-Field: name
    res->attributes[0] = acquire(sizeof(Object)).nullable;
    res->attributes[0]->type = Field;
    res->attributes[0]->data = acquire(sizeof(FieldData)).nullable;
    *((FieldData *) res->attributes[0]->data) = (FieldData) {
            .type=String,
            .value=new_string_instance(name, res)
    };

    // create sub-Field: value
    res->attributes[1] = acquire(sizeof(Object)).nullable;
    res->attributes[1]->type = Field;
    res->attributes[1]->data = acquire(sizeof(FieldData)).nullable;
    *((FieldData *) res->attributes[1]->data) = (FieldData) {
            .type=type,
            .value=dup(value)
    };

    return res;
}

Object *new_function_instance(
        void *(*impl)(),
        const char *name,
        Object *parent
) {
    Object *res = new_object(1);
    res->type = Function;
    res->data = impl;
    res->num_attributes = 1;
    res->attributes = acquire(sizeof(*res->attributes)).nullable;
    res->attributes[0] = acquire(sizeof(Object)).nullable;
    *((Object *) res->attributes[0]) = (Object) {
            .type=Field,
            .num_attributes=0,
            .attributes=NULL,
            .data=acquire(sizeof(FieldData)).nullable
    };
    ((FieldData *) res->attributes[0]->data)->type = String;
    ((FieldData *) res->attributes[0]->data)->value = new_string_instance(name, res);
    return res;
}


void *new_int(unsigned int n) {
    unsigned int *res = acquire(sizeof(unsigned int)).nullable;
    *res = n;
    return res;
}

#define NAME "__name__"
#define LENGTH "__len__"

void entry_point(void) {
//    THis is following diagrams/flow1.png
    declare_object(string__name__strlen);
    declare_object(string__len__strlen);
    declare_object(string__name__);
    declare_object(string__len__);
    declare_object(string__len__field__len__);
    declare_object(string__name__field__len__);
    declare_object(field__name__field__name__);
    declare_object(field__len__field__name);
    *string__name__strlen = init_object(Integer, 0, new_int(strlen("__name__")));
    *string__len__strlen = init_object(Integer, 0, new_int(strlen("__len__")));
    *field__name__field__name__ = init_object(Field, 1, string__name__);
    set_attr(field__name__field__name__, 0, field__name__field__name__);
    *string__name__ = init_object(String, 1, duplicate_string("__name__"));
    set_attr(string__name__, 0, string__name__field__len__);
    *string__name__field__len__ = init_object(Field, 1, string__name__strlen);
    *field__len__field__name = init_object(Field, 1, string__len__);
    set_attr(field__len__field__name, 0, field__name__field__name__);
    *string__len__ = init_object(String, 1, duplicate_string("__len__"));
    set_attr(string__len__, 0, string__len__field__len__);
    *string__len__field__len__ = init_object(Field, 1, string__len__strlen);
    set_attr(string__len__field__len__, 0, field__len__field__name);

    Object *o = getattr(string__len__, "__len__");
    printf("%d\n", *((unsigned int *) o->data));

}