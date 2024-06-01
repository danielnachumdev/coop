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
extern Object *Array;
extern Object *Boolean;
extern Object *Union;


Object *new_object(Object *type);

bool object_equals(const Object *a, const Object *b);

#endif //LOCAL_PLAYGROUND_OBJECT_H
