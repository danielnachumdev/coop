//
// Created by danie on 25/07/2024.
//

#include "List.h"
#include "Function.h"
#include "Node.h"

Object *List = NULL;

void __init_list(void) {
    List = new_object(Type);
    explicitsetfunc(List, __init__);
    explicitsetfunc(List, push);
    explicitsetfunc(List, popfirst);
    explicitsetfunc(List, poplast);
    explicitsetfunc(List, append);
    explicitsetfunc(List, isempty);
    explicitsetfunc(List, __bool__);
}

DEF(List, __init__, Object *, {
    Object *res = new_object(List);
    setattr(res, "head", NULL);
    setattr(res, "tail", NULL);
    return res;
}, void)

void _push(Object *self, Object *obj) {
    if (self == NULL || obj == NULL) return;
    if (getattr(self, "head") == NULL) {
        Object *new_head = explicitgetfunc(Node, __init__)(obj, NULL, NULL);
        setattr(self, "head", new_head);
        setattr(self, "tail", new_head);
    } else {
        Object *prev_head = getattr(self, "head");
        Object *new_head = explicitgetfunc(Node, __init__)(obj, prev_head, NULL);
        setattr(prev_head, "prev", new_head);
        setattr(self, "head", new_head);
    }
}

DEF(List, push, void, {
    _push(self, obj);
}, Object *self, Object *obj)

DEF(List, popfirst, Object *, {
    if (self == NULL) return NULL;
    if (explicitgetfunc(List, isempty)(self)) return NULL;
    Object *head = getattr(self, "head");
    Object *tail = getattr(self, "tail");
    setattr(self, "head", getattr(head, "next"));
    setattr(getattr(self, "head"), "prev", NULL);
    if (head == tail) {
        setattr(self, "head", NULL);
        setattr(self, "tail", NULL);
    }
    return head->data;
}, Object *self)

DEF(List, poplast, Object *, {
    if (self == NULL) return NULL;
    if (explicitgetfunc(List, isempty)(self)) return NULL;
    Object *head = getattr(self, "head");
    Object *tail = getattr(self, "tail");
    setattr(self, "tail", getattr(tail, "prev"));
    setattr(getattr(self, "tail"), "next", NULL);
    if (head == tail) {
        setattr(self, "head", NULL);
        setattr(self, "tail", NULL);
    }
    return tail->data;
}, Object *self)

DEF(List, append, void, {
    if (self == NULL || obj == NULL) return;
    if (getattr(self, "head") == NULL) {
        Object *new_head = explicitgetfunc(Node, __init__)(obj, NULL, NULL);
        setattr(self, "head", new_head);
        setattr(self, "tail", new_head);
    } else {
        Object *prev_tail = getattr(self, "tail");
        Object *new_tail = explicitgetfunc(Node, __init__)(obj, NULL, prev_tail);
        setattr(prev_tail, "next", new_tail);
        setattr(self, "tail", new_tail);
    }
}, Object *self, Object *obj)

DEF(List, __bool__, bool, {
    return explicitgetfunc(List, isempty)(self);
}, Object *self)

DEF(List, isempty, bool, {
    if (self == NULL) return true;
    return getattr(self, "head") == NULL;
}, Object *self)