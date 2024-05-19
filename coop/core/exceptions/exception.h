//
// Created by danie on 16/05/2024.
//

#ifndef MACROPYTHON_EXCEPTION_H
#define MACROPYTHON_EXCEPTION_H

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

void throw_impl(const Exception *e);

#define exception(name, msg) (Exception){name,msg,__LINE__,__FILE__,1,NULL}
#define exception_from(name, msg, exception_) (Exception){name,msg,__LINE__,__FILE__,1,&exception_}

#define throw(e) throw_impl(e)
#define easy_throw(name, msg) throw(&((Exception){name,msg,__LINE__,__FILE__,1,NULL}))
#define easy_throw_from(name, msg, exception) throw(&((Exception){name,msg,__LINE__,__FILE__,1,&exception}))

#endif //MACROPYTHON_EXCEPTION_H
