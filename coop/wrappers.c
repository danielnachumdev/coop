//
// Created by danie on 18/05/2024.
//
#include "core/macros.h"
#include "builtins.h"

#define INITIALIZE_TYPE_FULL(name, parent) \
Object PASTE2(type_,name) = (Object) { \
        .type=&PASTE2(type_,parent),\
        .num_attributes=0,\
        .attributes=NULL,\
        .data=NULL\
};                     \
Object * name = &PASTE2(type_,name)
#define INITIALIZE_TYPE(name) INITIALIZE_TYPE_FULL(name,Type)
INITIALIZE_TYPE(Type);
INITIALIZE_TYPE(Field);
INITIALIZE_TYPE(Function);
INITIALIZE_TYPE(Integer);
INITIALIZE_TYPE(String);
INITIALIZE_TYPE(Array);


