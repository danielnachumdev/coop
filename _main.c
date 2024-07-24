//
// Created by t-danachum on 21/05/2024.
//

#include "_main.h"
#include "coop/__init__.h"


DEF(Class, __init__, Object*, {
    Object *res = new_object(Type);
    setattr(res, "__name__", new_string(name));
    if (methods != NULL) {
        IndexT length = len(methods);
        for (IndexT i = 0; i < length; ++i) {
            Object *method = array_get(methods, i);
            setattr(res, getattr(method, "__name__")->data, method);
        }
    }
    return res;
}, const char *name, Object *methods)

DEF(Person, __init__, Object*, {
    Object *res = new_object(Type);
    setattr(res, "name", new_string(name));
    return res;
}, const char *name)

void _main(void) {
    Object *Class = new_object(Type);
    setfunc(Class, __init__);

    Object *person_methods = new_array(1, Function);
    array_set(person_methods, 0, new_function("__init__", cast(__init__Person, void*(*)()), NULL, NULL));

    Object *Person = getfunc(Class, __init__)("Person", person_methods);
    Object *danielPerson = getfunc(Person, __init__)("daniel");
    dir(danielPerson);
}