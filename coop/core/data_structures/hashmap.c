//
// Created by danie on 19/05/2024.
//

#include "hashmap.h"
#include "../memory/wrappers.h"

#define DEFAULT_NUM_BUCKETS 8
#define DEFAULT_SCALING_FACTOR 2
#define DEFAULT_SCALE_DOWN_THRESHOLD 0.25
#define DEFAULT_SCALE_UP_THRESHOLD 0.75

unsigned long hash(Hashmap *h, unsigned char *s) {
    if (h == NULL || s == NULL) return -1;
    unsigned long hash = 5381;
    int c;

    while ((c = (*(s++))))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

Hashmap *hashmap_new() {
    Hashmap *res = builtin_new(sizeof(Hashmap));
    if (res == NULL) return NULL;
    res->buckets = builtin_new(sizeof(Bucket) * DEFAULT_NUM_BUCKETS);
    if (res->buckets == NULL) {
        builtin_free(res);
        return NULL;
    }
    for (int i = 0; i < DEFAULT_NUM_BUCKETS; ++i) {
        res->buckets[i] = linked_list_new();
        if (res->buckets[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                builtin_free(res->buckets[j]);
            }
            builtin_free(res->buckets);
            builtin_free(res);
            return NULL;
        }
    }
    res->num_buckets = DEFAULT_NUM_BUCKETS;
    res->count = 0;
    res->change_factor = DEFAULT_SCALING_FACTOR;
    res->scale_down_threshold = DEFAULT_SCALE_DOWN_THRESHOLD;
    res->scale_up_threshold = DEFAULT_SCALE_UP_THRESHOLD;

}

void hashmap_free(Hashmap **pph) {
    if (pph == NULL) return;
    if (*pph == NULL) return;
    for (int i = 0; i < (*pph)->num_buckets; ++i)
        linked_list_free(&((*pph)->buckets[i]));
    builtin_free((*pph)->buckets);
    builtin_free(*pph);
    *pph = NULL;
}

Node *hashmap_get(Hashmap *h, void *p) {
    if (h == NULL || p == NULL) return NULL;
}

Node *hashmap_del(Hashmap *h, void *p) {
    if (h == NULL || p == NULL) return NULL;
}

Node *hashmap_add(Hashmap *h, void *p) {
    if (h == NULL || p == NULL) return NULL;
}


//
//
//IRandomAccess random_access_hash_map = {
//        .data_structure=NULL,
//        .free_structure=random_access_linked_list_free,
//        .at=random_access_linked_list_at,
//        .num_buckets=random_access_linked_list_length,
//        .contains=random_access_linked_list_contains,
//        .append=random_access_linked_list_append,
//        .insert=random_access_linked_list_insert,
//        .remove=random_access_linked_list_remove
//};