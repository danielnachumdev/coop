//
// Created by danie on 25/07/2024.
//

#include "Node.h"
#include "Function.h"
#include "String.h"

Object *Node = NULL;

void __init_node(void) {
    Node = new_object(Type);
    setattr(Node, "__name__", implicitgetfunc(String, __init__)("Node"));
    implicitsetfunc(Node, __init__);
}

DEF(Node, __init__, Object*, {
    Object *res = new_object(Node);
    res->data = data;
    setattr(res, "next", next);
    setattr(res, "prev", prev);
    return res;
}, Object *data, Object *next, Object *prev);