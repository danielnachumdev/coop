//
// Created by t-danachum on 27/05/2024.
//

#ifndef LOCAL_PLAYGROUND_FIELD_H
#define LOCAL_PLAYGROUND_FIELD_H

#include "../../object.h"

void init_field(void);

Object *new_field(Object *name_field, Object *value);
void append_field(Object *obj, Object *field);
#endif //LOCAL_PLAYGROUND_FIELD_H
