//
// Created by t-danachum on 21/05/2024.
//

#include "_main.h"
#include "coop/__init__.h"

void _main(void) {
//    dir(__global__name__attr__, true, NULL, NULL,NULL);
    Object *obj = new_object(Type);
    obj->num_attributes = 1;
    obj->attributes = acquire(sizeof(Object *));
    obj->attributes[0] = new_attr("life",new_integer(1));

    dir(obj, false);
}