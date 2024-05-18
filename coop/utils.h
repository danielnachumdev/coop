//
// Created by danie on 17/05/2024.
//

#ifndef MACROPYTHON_UTILS_H
#define MACROPYTHON_UTILS_H

#include "structs/optional.h"

Optional concatenate_strings(unsigned int n, ...);
Optional join_strings(const char* s1, const char* s2);

Optional duplicate_string(const char *s);

#endif //MACROPYTHON_UTILS_H
