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

#define F(x) STR(x)," => ", x


Object *get(Object *obj, const char *key) {
    if (obj == NULL || key == NULL) return NULL;
    for (int i = 0; i < obj->num_attributes; ++i) {
        Object *attr = obj->attributes[i];
        if (attr->type == Field) {
            if (attr->data != NULL) {
                if (((FieldData *) attr->data)->type == String)
                    if (strcmp(((Object *) ((FieldData *) attr->data)->value)->data, key) == 0)
                        return ((FieldData *) attr->data)->value;
            }
        }
    }
    return NULL;
}

bool contains(const Object *obj, const char *key) {
    return get((Object *) obj, key) != NULL;
}

Object *set(Object *obj, const char *key, Object *value) {
    Object *existing_object = get(obj, key);
    if (existing_object == NULL) {

    } else {

    }

}

void dir(const Object *obj) {
    if (obj == NULL) return;
    for (unsigned int i = 0; i < obj->num_attributes; ++i) {
        Object *attr = obj->attributes[i];
        for (unsigned int j = 0; j < attr->num_attributes; ++j) {
            Object *sub_attr = attr->attributes[j];
            if (sub_attr->type == Field) {
                FieldData *fd = sub_attr->data;
                assert(fd->type == String);
                char *name = ((Object *) fd->value)->data;
                printf("%s", name);
            }
        }
    }
}


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

void _main(void) {
    Object *name_object_name_object = new_object(1);
    Object *name_object_name_field = new_object(1);
    FieldData *name_object_name_field_fielddata = acquire(sizeof(FieldData)).nullable;
    Object *name_object_name_field_length_object = new_object(1);
    Object *length_object_name_field = new_object(1);
    FieldData *length_object_name_field_fielddata = acquire(sizeof(FieldData)).nullable;
    Object *length_object_name_field_name_object = new_object(1);

    *name_object_name_object = init_object(String, 1, duplicate_string("name"));
    set_attr(name_object_name_object, 0, name_object_name_field);
    *name_object_name_field = init_object(Field, 1, name_object_name_field_fielddata);
    *name_object_name_field_fielddata = init_fielddata(String, name_object_name_object);
    set_attr(name_object_name_field, 0, name_object_name_field_length_object);
    *name_object_name_field_length_object = init_object(Integer, 1, acquire(sizeof(unsigned int *)).nullable);
    *((unsigned int *) name_object_name_field_length_object->data) = strlen(name_object_name_object->data);
    set_attr(name_object_name_field_length_object, 0, length_object_name_field);
    *length_object_name_field = init_object(Field, 1, length_object_name_field_fielddata);
    *length_object_name_field_fielddata = init_fielddata(String, length_object_name_field_name_object);
    *length_object_name_field_name_object = init_object(String, 1, duplicate_string("length"));
    set_attr(length_object_name_field_name_object, 0, length_object_name_field);

}