//
// Created by danie on 24/07/2024.
//

#ifndef COOP_CALL_H
#define COOP_CALL_H
#define invoke(obj,name,...) cast(getattr(obj,name)->data,void * (*)())(__VA_ARGS__)
#define call(obj, ...) invoke(obj,"__call__",__VA_ARGS__)
#endif //COOP_CALL_H
