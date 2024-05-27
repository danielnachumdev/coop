//
// Created by danie on 20/05/2024.
//

#ifndef COOP_STR_H
#define COOP_STR_H


const char *int_to_string(const int n) {

}

const char *float_to_string(const float f) {

}

const char *double_to_string(const double d) {

}

const char *char_to_string(const char c) {

}

const char *long_to_string(const long l) {

}

#define str(x) _Generic(x,                      \
    int:int_to_string(x),                       \
    char: char_to_string(x),                    \
    float:float_to_string(x),                   \
    double:double_to_string(x),                 \
    long: long_to_string(x),                    \
    long long: long_to_string(x),               \
    unsigned long long: long_to_string(x)       \
)


#endif //COOP_STR_H
