//
// Created by t-danachum on 22/05/2024.
//

#ifndef LOCAL_PLAYGROUND_OBJECT_H
#define LOCAL_PLAYGROUND_OBJECT_H

#include <stdbool.h>
#include <stddef.h>

struct Attribute;
typedef struct Object {
    const struct Object *type;
    unsigned long num_attributes;
    struct Attribute **attributes;
    void *data;
} Object;

typedef struct Attribute {
    const char *key;
    Object *value;
} Attribute;

extern Object *Type;
extern Object *String;
extern Object *Number;
extern Object *Integer;
extern Object *Function;
extern Object *Array;
extern Object *Boolean;
extern Object *Union;
extern Object *Node;
extern Object *List;


Object *_new_object_impl(Object *type);

#define new_object(type) _new_object_impl(type)

bool object_equals(const Object *a, const Object *b);

Attribute *new_attr(const char *key, Object *value);


#endif //LOCAL_PLAYGROUND_OBJECT_H
