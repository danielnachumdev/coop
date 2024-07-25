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

Object *super(const Object *self, IntegerT steps) {
    if (self == NULL) return NULL;
    if (steps < 0) return NULL;
    if (steps == 0) return (Object *) self;

}

DEF(Animal, __init__, Object*, {
    Object *res = new_object(Animal);
    setattr(res, "__name__", explicitgetfunc(String, __init__)(name));
    return res;
}, const char *name)


DEF(Animal, speak, void, {
    if (self == NULL) return;
    printf("hello\n");
}, const Object *self)

void main(void) {
    Animal = explicitgetfunc(Type, __init__)("Animal", 0l, (Object[]) {}, 0l, (Attribute[]) {});
    explicitsetfunc(Animal, __init__);
    dir(Animal);
    Object *Dog = explicitgetfunc(Animal, __init__)("Dog");
    Object *Cat = explicitgetfunc(Animal, __init__)("Cat");
    dir(Dog);
    dir(Cat);

//    explicitgetfunc(Dog, speak)();
//    explicitgetfunc(Cat, speak)();
}
