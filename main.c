//
// Created by danie on 18/05/2024.
//
#include "coop/__init__.h"


//DEF(Class, __init__, Object*, {
//    Object *res = new_object(Type);
//    setattr(res, "__name__", __new_string(name));
//    if (methods != NULL) {
//        IndexT length = len(methods);
//        for (IndexT i = 0; i < length; ++i) {
//            Object *method = array_get(methods, i);
//            setattr(res, getattr(method, "__name__")->data, method);
//        }
//    }
//    return res;
//}, const char *name, Object *methods)
//
//DEF(Person, __init__, Object*, {
//    Object *res = new_object(Type);
//    setattr(res, "name", __new_string(name));
//    return res;
//}, const char *name)
//
//DEF(Person, say_hello, void, {
//    println(__new_string("Hello!!"));
//}, void)

//void linkedlist_print(LinkedList *ll) {
//    Node *cur = ll->head;
//    while (cur != NULL) {
//        printf("Node(data=%p)\n",cur->data);
//        cur = cur->next;
//    }
//}

void main(void) {
//    Object *Class = new_object(Type);
//    explicitsetfunc(Class, __init__);
//    Object *person_methods = new_array(1, Function);
//    array_set(person_methods, 0, __new_function("__init__", cast(Person__init__, void*(*)()), NULL, NULL));
//
//    Object *Person = explicitgetfunc(Class, __init__)("Person", person_methods);
//    explicitsetfunc(Person, say_hello);
//    Object *danielPerson = explicitgetfunc(Person, __init__)("daniel");
////    dir(danielPerson);
//    explicitgetfunc(Person, say_hello)();
//    dir(String);
//    linkedlist_print(__global_allocator__->structure);
}




