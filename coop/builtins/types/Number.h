//
// Created by t-danachum on 27/05/2024.
//

#ifndef LOCAL_PLAYGROUND_NUMBER_H
#define LOCAL_PLAYGROUND_NUMBER_H

#include "../object.h"

void __init_number(void);

void number_print(const Object *obj);

bool number_equals(const Object *a, const Object *b);

#endif //LOCAL_PLAYGROUND_NUMBER_H
