//
// Created by t-danachum on 22/05/2024.
//

#ifndef LOCAL_PLAYGROUND_OBJECT_H
#define LOCAL_PLAYGROUND_OBJECT_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Object {
    const struct Object *type;
    unsigned long num_attributes;
    struct Object **attributes;
    bool has_data;
    void *data;
} Object;

extern Object *Type;
extern Object *String;
extern Object *Number;
extern Object *Integer;
extern Object *Address;
extern Object *Function;
extern Object *Field;
extern Object *Array;
extern Object *NoneType;
extern Object *None;

#define init_object(type_) (Object){ \
    .type=type_,                     \
    .num_attributes=0,               \
    .attributes=NULL,                \
    .has_data=false,                 \
    .data=NULL                       \
}

#endif //LOCAL_PLAYGROUND_OBJECT_H
