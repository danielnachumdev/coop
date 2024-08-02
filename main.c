//
// Created by danie on 18/05/2024.
//
#include "coop/__init__.h"

void dirall(void) {
    dir(Type);
    dir(Number);
    dir(Integer);
    dir(String);
    dir(Function);
    dir(Array);
    dir(Union);
    dir(Boolean);
}

int main(void) {
    Object *name = strinput("What is your name? ");
    print(S("Your name is:"), name);
    dir(Set);
    return 0;
}

