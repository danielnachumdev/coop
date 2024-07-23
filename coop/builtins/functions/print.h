//
// Created by danie on 28/05/2024.
//

#ifndef COOP_PRINT_H
#define COOP_PRINT_H

#include "../object.h"
#include "../macros.h"
void __print_object(Object *obj);
void _print_imp(const char *sep, const char *end, unsigned int n, ...);

#define print(...) _print_imp(" ","", NUM_POINTERS(__VA_ARGS__), ## __VA_ARGS__)
#define println(...) _print_imp(" ","\n", NUM_POINTERS(__VA_ARGS__), ## __VA_ARGS__)

#endif //COOP_PRINT_H
