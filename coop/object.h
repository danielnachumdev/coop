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
    void *data;
} Object;

extern Object *Type;
extern Object *String;
extern Object *Number;
extern Object *Integer;
extern Object *Function;
extern Object *Field;

#define init_object(type_) (Object){ \
    .type=type_,                     \
    .num_attributes=0,               \
    .attributes=NULL,                \
    .data=NULL                       \
}

#endif //LOCAL_PLAYGROUND_OBJECT_H
