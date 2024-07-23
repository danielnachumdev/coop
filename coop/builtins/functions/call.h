//
// Created by danie on 24/07/2024.
//

#ifndef COOP_CALL_H
#define COOP_CALL_H
#define call(obj, ...) cast(getattr(obj,"__call__")->data,void * (*)())(__VA_ARGS__)
#endif //COOP_CALL_H
