//
// Created by danie on 28/05/2024.
//

#include <string.h>
#include "../../../globals.h"

Object *getattr(const Object *obj, const char *name) {
    if (obj == NULL || name == NULL) return NULL;
    for (unsigned int i = 0; i < obj->num_attributes; ++i) {
        Object *attr = obj->attributes[i];
        if (attr->type != Field) continue;
        for (unsigned int j = 0; j < attr->num_attributes; ++j) {
            Object *subattr = attr->attributes[j];
            if (subattr->type != Field) continue;
            for (int k = 0; k < subattr->num_attributes; ++k) {
                Object *subsubattr = subattr->attributes[k];
                if (subsubattr->type != Field) continue;
                if (cast(subsubattr->data, Object *)->type != String) continue;
                if (strcmp(cast(subsubattr->data, Object *)->data, NAME) == 0)
                    return cast(attr->data, Object *);
            }
        }
    }
    return NULL;
}