//
// Created by danie on 19/05/2024.
//

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "globals.h"

Object *get(Object *obj, const char *key) {
    if (obj == NULL || key == NULL) return NULL;
    for (int i = 0; i < obj->num_attributes; ++i) {
        Object *attr = obj->attributes[i];
        for (int j = 0; j < attr->num_attributes; ++j) {
            Object *sub_attr_data = attr->attributes[j]->data;
            if (sub_attr_data->type != String) continue;

        }
        if (attr->type == Field) {
            Object *field = attr;
            if (field->data == NULL)
                continue;
            if (((FieldData *) attr->data)->type == String)
                if (strcmp(((Object *) ((FieldData *) attr->data)->value)->data, key) == 0)
                    return ((FieldData *) attr->data)->value;
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
