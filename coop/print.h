//
// Created by danie on 18/05/2024.
//

#ifndef MACROPYTHON_PRINT_H
#define MACROPYTHON_PRINT_H

#include "utils.h"

void print_imp(const char *sep, const char *end, unsigned int n, ...);

#define print(...) print_imp(" ","\n", NUM_POINTERS(__VA_ARGS__), ## __VA_ARGS__)
#endif //MACROPYTHON_PRINT_H
