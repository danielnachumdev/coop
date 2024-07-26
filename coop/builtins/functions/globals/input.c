//
// Created by danie on 26/07/2024.
//

#include "input.h"
#include "print.h"

#define MAX_LENGTH 1000

Object *input(const Object *string) {
    print(string);
    char buffer[MAX_LENGTH] = {0};
    fgets(buffer, MAX_LENGTH, stdin);
    return implicitgetfunc(String, __init__)(buffer);
}