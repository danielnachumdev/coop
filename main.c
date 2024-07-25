//
// Created by danie on 18/05/2024.
//
#include "coop/__init__.h"

void dirall(void) {
    dir(Type);
    dir(Number);
    dir(Integer);
    dir(String);
    dir(Function);
    dir(Array);
    dir(Union);
    dir(Boolean);
}

Object *Animal = NULL;


DEF(Animal, __init__, Object*, {
    Object *res = new_object(Animal);
    setattr(res, "animal_type", explicitgetfunc(String, __init__)(name));
    return res;
}, const char *name)

Object *Dog = NULL;

DEF(Animal, speak, void, {
    if (self == NULL) return;
    printf("*animal noises*\n");
}, const Object *self)

DEF(Dog, speak, void, {
    if (self == NULL) return;
    cast(getattr(super(self, 1), "speak")->data, Animalspeak_prototype)(self);
    printf("*woof woof*\n");
}, const Object *self)

DEF(Dog, __init__, Object *, {
    if (name == NULL) return NULL;
    Object *res = cast(getattr(super(Dog, 1), "__init__")->data, Animal__init___prototype)("Dog");
    setattr(res, "animal_name", explicitgetfunc(String, __init__)(name));
    return res;
}, const char *name)

void main(void) {
    Animal = explicitgetfunc(Type, __init__)("Animal", 0l, (Object[]) {}, 0l, (Attribute[]) {});
    explicitsetfunc(Animal, __init__);
    explicitsetfunc(Animal, speak);
    Dog = explicitgetfunc(Animal, __init__)("Dog");
    explicitgetfunc(Dog, speak)(Dog);
    explicitsetfunc(Dog, speak);
    explicitgetfunc(Dog, speak)(Dog);
}

