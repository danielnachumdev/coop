//
// Created by danie on 28/05/2024.
//

#ifndef COOP_EXCEPTION_H
#define COOP_EXCEPTION_H

#include <stdlib.h>
#include <stdio.h>

#define KeyError "KeyError"
typedef struct Exception {
    char *name;
    char *msg;
    long unsigned int line_number;
    char *filename;
    int exit_code;
    struct Exception *parent;
} Exception;

extern void throw_impl(const Exception *e);

#define exception(name, msg) (Exception){name,msg,__LINE__,__FILE__,1,NULL}
#define exception_from(name, msg, exception_) (Exception){name,msg,__LINE__,__FILE__,1,&exception_}

#define throw(name, msg) throw_impl(&((Exception){name,msg,__LINE__,__FILE__,1,NULL}))
#define throw_from(name, msg, exception) throw_impl(&((Exception){name,msg,__LINE__,__FILE__,1,&exception}))

#endif //COOP_EXCEPTION_H
