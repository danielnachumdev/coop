//
// Created by t-danachum on 21/05/2024.
//

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "_main.h"
#include "coop/memory/allocator.h"
#include "coop/object.h"
#include "coop/macros.h"

Object *getattr(const Object *obj, const char *name) {
    if (obj == NULL || name == NULL) return NULL;
    for (unsigned int i = 0; i < obj->num_attributes; ++i) {
        Object *attr = obj->attributes[i];
        if (attr->type != Field) continue;
        for (unsigned int j = 0; j < attr->num_attributes; ++j) {
            Object *subattr = attr->attributes[j];
            if (subattr->type != Field) continue;
            for (int k = 0; k < subattr->num_attributes; ++k) {
                Object *subsubattr = subattr->attributes[k];
                if (subsubattr->type != Field) continue;
                if (cast(subsubattr->data, Object*)->type != String) continue;
                if (strcmp(cast(subsubattr->data, Object*)->data, NAME) == 0)
                    return cast(subattr->data, Object*);
            }
        }
    }
    return NULL;
}


void setattr(Object *obj, const char *name, const Object *value) {

}

bool hasattr(Object *obj, const char *name) {
    return getattr(obj, name) != NULL;
}

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

void print_object(const Object *obj, const char *end);

#define print(obj) print_object(obj,"")
#define println(obj) print_object(obj,"\n")

void print_object(const Object *obj, const char *end) {
    if (obj == NULL) return;
    if (obj->type == Integer) {
//        printf("Integer(%d)%s", *((const int *) obj->data), end);
        printf("%d%s", *((const int *) obj->data), end);
    } else if (obj->type == String) {
//        printf("String(\"%s\")%s", ((const char *) obj->data), end);
        printf("\"%s\"%s", ((const char *) obj->data), end);
    } else if (obj->type == Field) {
        printf("Field(name=");
        print(getattr(obj, NAME));
        printf(", value=");
        print(obj->data);
        printf(")%s", end);
    }

}


void _main(void) {
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