//
// Created by danie on 17/05/2024.
//
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "coop/builtins.h"
#include "coop/core/print.h"
#include "coop/core/macros.h"
#include "coop/core/memory_management//allocator.h"
#include "coop/core/logging/logger.h"
#include "coop/duplicators.h"
#include "coop/globals.h"

#define F(x) STR(x)," => ", x


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
    Object *res = acquire(sizeof(Object)).nullable;
    res->type = String;
    res->num_attributes = 0;
    res->attributes = NULL;
    res->data = duplicate_string(s);
//    res->num_attributes = 1;
//    res->attributes = acquire(sizeof(*res->attributes)).nullable;
//    unsigned int *data = acquire(sizeof(data)).nullable;
//    *data = strlen(s);
//    if (parent->type == Field) {
//        *(res->attributes[0]) = (Object) {
//                .type=Field,
//                .data=acquire(sizeof(FieldData)).nullable
//        };
//        *((FieldData *) res->attributes[0]->data) = (FieldData) {
//                .type=String,
//                .value=duplicate_string("Length")
//        };
//    } else {
//        res->attributes[0] = new_field_instance(
//                "Length",
//                Integer,
//                data,
//                (void *(*)(const void *)) duplicate_integer,
//                res
//        );
//    }
//    res->data = duplicate_string(s);
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

void *new_int(unsigned int n) {
    unsigned int *res = acquire(sizeof(unsigned int)).nullable;
    *res = n;
    return res;
}

#define NAME "__name__"
#define LENGTH "__len__"

void entry_point(void) {
//    NOTE: "dot notation" is symbolic and not actually possible. It means that an object has some attr with the same name.
//    the String "__name__"
    declare_object(string_name);
    *string_name = init_object(String, 2, duplicate_string(NAME));
//    "__name__".__len__ = Field
    declare_object(string_name_length_field);
    set_attr(string_name, 0, string_name_length_field);
//    "__name__".__len__.data = strlen("__name__")
    declare_object(string_name_length_field_value_object);
    *string_name_length_field = init_object(Field, 1, string_name_length_field_value_object);
    *string_name_length_field_value_object = init_object(Integer, 0, new_int(strlen(NAME)));
//    "__name__".__name__ = Field
    declare_object(string_name_name_field);
    set_attr(string_name, 1, string_name_name_field);
    *string_name_name_field = init_object(Field, 1, string_name);
//    "__name__".__name__.__name__ = "__name__".__name__
    set_attr(string_name_name_field, 0, string_name_name_field);

    get(string_name, "__len__");




//    the String "__len__"
    declare_object(string_length);
    *string_length = init_object(String, 1, duplicate_string(LENGTH));
//    create "__len__".__len__
    declare_object(string_length_length_field);
    set_attr(string_length, 0, string_length_length_field);
//    "__len__".__len__ = strlen("__len__")
    declare_object(string_length_length_field_value_object);
    *string_length_length_field = init_object(Field, 1, string_length_length_field_value_object);
    *string_length_length_field_value_object = init_object(Integer, 0, new_int(strlen(LENGTH)));

//    but the there exists "__len__".__len__

}