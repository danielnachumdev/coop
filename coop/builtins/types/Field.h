//
// Created by t-danachum on 27/05/2024.
//

#ifndef LOCAL_PLAYGROUND_FIELD_H
#define LOCAL_PLAYGROUND_FIELD_H

#include "../../object.h"

void __init_field(void);

Object *new_field_explicit(Object *name_field, Object *value);

void append_field(Object *obj, Object *field);

Object *new__name__field(const char *name);
Object *new__len__field(unsigned long n);
#endif //LOCAL_PLAYGROUND_FIELD_H
