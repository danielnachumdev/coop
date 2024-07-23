//
// Created by danie on 24/07/2024.
//

#include <string.h>
#include "__attr_utils.h"

bool get_attr_index(const Object *obj, const char *key, unsigned int *index_output) {
    if (obj == NULL || key == NULL || index_output == NULL) return false;
    for (int i = 0; i < obj->num_attributes; ++i) {
        Attribute *attr = obj->attributes[i];
        if (strcmp(attr->key, key) == 0) {
            *index_output = i;
            return true;
        }
    }
    return false;
}