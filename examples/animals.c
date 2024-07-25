//
// Created by danie on 26/07/2024.
//
#include "../coop/__init__.h"

Object *Animal = NULL;
Object *Dog = NULL;


DEF(Animal, __init__, Object*, {
    Object *res = new_object(Animal);
    setattr(res, "animal_type", explicitgetfunc(String, __init__)(name));
    return res;
}, const char *name)


DEF(Animal, speak, void, {
    if (self == NULL) return;
    printf("*animal noises*\n");
}, const Object *self)

DEF(Dog, speak, void, {
    if (self == NULL) return;
    cast(getattr(super(self, 1), "speak")->data, Animalspeak_prototype)(self);
    print(getattr(self, "animal_name"), explicitgetfunc(String, __init__)("the"), getattr(self, "animal_type"));
    printf(": *woof woof*\n");
}, const Object *self)

DEF(Dog, __init__, Object *, {
    if (name == NULL) return NULL;
    Object *res = superfunc(Dog, 1, "__init__", Animal__init___prototype)("Dog");
    setattr(res, "animal_name", explicitgetfunc(String, __init__)(name));
    return res;
}, const char *name)

int main(void) {
    Animal = explicitgetfunc(Type, __init__)("Animal", 0l, (Object[]) {}, 0l, (Attribute[]) {});
    explicitsetfunc(Animal, __init__);
    explicitsetfunc(Animal, speak);
    Dog = explicitgetfunc(Animal, __init__)("Dog");
    explicitsetfunc(Dog, __init__);
    Object *rocky = explicitgetfunc(Dog, __init__)("Rocky");
    explicitgetfunc(Dog, speak)(rocky);
    explicitsetfunc(Dog, speak);
    explicitgetfunc(Dog, speak)(rocky);
    return 0;
}
