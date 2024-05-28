//
// Created by t-danachum on 27/05/2024.
//

#ifndef LOCAL_PLAYGROUND_STRING_H
#define LOCAL_PLAYGROUND_STRING_H

#include "../../object.h"

void init_string(void);
Object *new_string(const char *s, Object *length_field);
#endif //LOCAL_PLAYGROUND_STRING_H
