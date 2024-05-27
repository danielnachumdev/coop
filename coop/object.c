//
// Created by t-danachum on 22/05/2024.
//

#include <string.h>
#include "object.h"
#include "memory/allocator.h"

//
//Object *default_new_primitive(Object *type, const void *obj, void *(*dup_func)(const void *obj)) {
//    Object *res = acquire(sizeof(Object));
//    if (res == NULL) return NULL;
//    res->data = dup_func(obj);
//    *res = init_object(type);
//    return res;
//}
//
//#define new_primitive(type, obj, dup_func) default_new_primitive(String, (const void *) obj, (void *(*)(const void *)) dup_func)
//#define default_name(type) default_new_##type
//#define declare_default_new_primitive(type) \
//Object * default_name(type)(const void * obj, void *(*dup_func)(const void *obj)){ \
//    return new_primitive(type,obj,dup_func);                                             \
//}
//
//declare_default_new_primitive(String)
//
//declare_default_new_primitive(Integer)
//
//
//char *duplicate_string(const char *s) {
//    char *res = acquire(strlen(s) + 1);
//    if (res == NULL) return NULL;
//    strcpy(res, s);
//    return res;
//}

//void init_types(void) {
//    Type = acquire(sizeof(Object));
//    *Type = init_object(Type);
//
//    String = acquire(sizeof(Object));
//    *String = init_object(Type);
//    String->has_data = true;
//
//    Number = acquire(sizeof(Object));
//    *Number = init_object(Type);
//    Number->has_data = true;
//
//    Integer = acquire(sizeof(Object));
//    *Integer = init_object(Number);
//    Integer->has_data = true;
//
//    Address = acquire(sizeof(Object));
//    *Address = init_object(Integer);
//    Address->has_data = true;
//
//    Function = acquire(sizeof(Object));
//    *Function = init_object(Type);
//
//    Field = acquire(sizeof(Object));
//    *Field = init_object(Type);
//
//    Field = acquire(sizeof(Object));
//    *Field = init_object(Type);
//
//    Array = acquire(sizeof(Object));
//    *Array = init_object(Type);
//
//    NoneType = acquire(sizeof(Object));
//    *NoneType = init_object(Type);
//
//    None = acquire(sizeof(Object));
//    *None = init_object(NoneType);
//}
