//
// Created by t-danachum on 27/05/2024.
//

#ifndef LOCAL_PLAYGROUND_STRING_H
#define LOCAL_PLAYGROUND_STRING_H

#include "../object.h"

void __init_string(void);

Object *new_string_explicit(const char *s, Object *length_field);

Object *new_string(const char *s);

bool string_equals(const Object *a, const Object *b);

void string_print(const Object *s);

#endif //LOCAL_PLAYGROUND_STRING_H
