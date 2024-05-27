//
// Created by danie on 17/05/2024.
//

#ifndef MACROPYTHON_INTERFACE_RANDOM_ACCESS_H
#define MACROPYTHON_INTERFACE_RANDOM_ACCESS_H
typedef struct IRandomAccess {
    void *data_structure;

    void (*free_structure)(struct IRandomAccess *self);

    void *(*at)(struct IRandomAccess *self, long unsigned int index);

    long unsigned int (*length)(struct IRandomAccess *self);

    void *(*contains)(struct IRandomAccess *self, void *p);

    void *(*append)(struct IRandomAccess *self, void *p);

    void *(*insert)(struct IRandomAccess *self, void *p, long unsigned int index);

    void (*remove)(struct IRandomAccess *self, void *p);
} IRandomAccess;

#endif //MACROPYTHON_INTERFACE_RANDOM_ACCESS_H
