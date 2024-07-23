//
// Created by t-danachum on 21/05/2024.
//

#include "_main.h"
#include "coop/__init__.h"

Object *class_init(const char *name, Object *methods) {
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
}

Object *new_person(const char *name) {
    Object *res = new_object(Type);
    setattr(res, "name", new_string(name));
    return res;
}

void _main(void) {
    Object *Class = new_object(Type);
    setattr(Class, "__init__", new_function("__init__", cast(class_init, void*(*)()), NULL, NULL));

    Object *person_methods = new_array(1, Function);
    array_set(person_methods, 0, new_function("__init__", cast(new_person, void*(*)()), NULL, NULL));

    Object *Person = init(Class, Object *(*)(const char *, Object*), "Person", person_methods);

    Object *danielPerson = init(Person, Object *(*)(const char *), "daniel");
    dir(danielPerson);
}