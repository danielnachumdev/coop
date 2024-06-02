//
// Created by danie on 30/05/2024.
//

#include <assert.h>
#include <memory.h>
#include "test_hashset.h"
#include "../../coop/data_structures/hashset.h"

void hashmap_naive_free(void *p) {
    builtin_free(p);
}

void *hashmap_int_dup(const void *p) {
    int *res = builtin_new(sizeof(int));
    *res = *(int *) p;
    return res;
}

bool hashmap_int_comparer(const void *p1, const void *p2) {
    return *(int *) p1 == *(int *) p2;
}

unsigned long integer_hash(const void *p) {
    int x = *(int *) p;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return (unsigned long) x;
}

void test_hashset_creation() {
    // Test creation of hashmap
    HashSet *map = hashset_new(hashmap_int_dup, hashmap_naive_free, hashmap_int_comparer,
                               &default_hashset_strategy, integer_hash);
    assert(map != NULL);

    assert(memcmp(map->strategy, &default_hashset_strategy, sizeof(HashSetStrategy)) == 0);
    hashset_free(&map);
    assert(map == NULL);
}

void test_hashset_insertion_and_removal() {
    // Test insertion and removal of elements
    HashSet *map = hashset_new(hashmap_int_dup, hashmap_naive_free, hashmap_int_comparer, &default_hashset_strategy,
                               integer_hash);
    assert(map != NULL);

    int data1 = 42;
    int data2 = 123;

    // Insertion
    assert(hashset_add(map, &data1));
    assert(hashset_add(map, &data2));

    // Check contains
    assert(hashset_contains(map, &data1));
    assert(hashset_contains(map, &data2));

    // Removal
    hashset_remove(map, &data1);
    assert(!hashset_contains(map, &data1));
    assert(hashset_contains(map, &data2));

    hashset_remove(map, &data2);
    assert(!hashset_contains(map, &data2));

    hashset_free(&map);
    assert(map == NULL);
}

void test_hashset_contains() {
    // Test contains function
    HashSet *map = hashset_new(hashmap_int_dup, hashmap_naive_free, hashmap_int_comparer, &default_hashset_strategy,
                               integer_hash);
    assert(map != NULL);

    int data1 = 42;
    int data2 = 123;

    // Insertion
    assert(hashset_add(map, &data1));
    assert(hashset_add(map, &data2));

    // Check contains
    assert(hashset_contains(map, &data1));
    assert(hashset_contains(map, &data2));

    // Check non-existent element
    int data3 = 456;
    assert(!hashset_contains(map, &data3));

    hashset_free(&map);
    assert(map == NULL);
}

void test_hashset_insert_duplicate() {
    // Test insertion of duplicate element
    HashSet *map = hashset_new(hashmap_int_dup, hashmap_naive_free, hashmap_int_comparer, &default_hashset_strategy,
                               integer_hash);
    assert(map != NULL);

    int data1 = 42;

    // Insertion
    assert(hashset_add(map, &data1));

    // Attempt to insert duplicate
    assert(hashset_add(map, &data1));

    hashset_free(&map);
    assert(map == NULL);
}

void test_hashset_remove_nonexistent() {
    // Test removal of non-existent element
    HashSet *map = hashset_new(hashmap_int_dup, hashmap_naive_free, hashmap_int_comparer, &default_hashset_strategy,
                               integer_hash);
    assert(map != NULL);

    int data1 = 42;

    // Insertion
    assert(hashset_add(map, &data1));

    // Attempt to remove non-existent element
    int data2 = 123;
    hashset_remove(map, &data2);

    // Verify original element still exists
    assert(hashset_contains(map, &data1));

    hashset_free(&map);
    assert(map == NULL);
}

void test_hashset_resize_up() {
    // Test resizing up
    HashSetStrategy strategy = {0.1, 0.9, 2.0, 2}; // Initial length is 5
    HashSet *map = hashset_new(hashmap_int_dup, hashmap_naive_free, hashmap_int_comparer, &strategy, integer_hash);
    assert(map != NULL);

    // Insert elements to trigger resize up
    for (int i = 0; i < 4; ++i) {
        assert(hashset_add(map, &i));
    }

    // Verify length increased after resize up
    assert(map->length > 5);

    hashset_free(&map);
}

void test_hashset_resize_down() {
    // Test resizing down
    HashSetStrategy strategy = {0.5, 0.9, 2.0, 10}; // Initial length is 20
    HashSet *map = hashset_new(hashmap_int_dup, hashmap_naive_free, hashmap_int_comparer, &strategy, integer_hash);
    assert(map != NULL);

    // Insert elements to trigger resize down
    for (int i = 0; i < 15; ++i) {
        assert(hashset_add(map, &i));
    }

    for (int i = 0; i < 10; ++i) {
        hashset_remove(map, &i);
    }

    // Verify length decreased after resize down
    assert(map->length < 20);

    hashset_free(&map);
}

void my_test(void) {
    HashSet *h = hashset_new(hashmap_int_dup, hashmap_naive_free, hashmap_int_comparer, &default_hashset_strategy,
                             integer_hash);
    assert(h != NULL);
    for (int i = 0; i < 1000; ++i) {
        hashset_add(h, &i);
    }

    hashset_free(&h);
}

void test_hashset(void) {
    printf("Testing HashSet - STARTED\n");
    test_hashset_creation();
    test_hashset_insertion_and_removal();
    test_hashset_insert_duplicate();
    test_hashset_contains();
    test_hashset_remove_nonexistent();
    test_hashset_resize_up();
    test_hashset_resize_down();
//    my_test();
    printf("Testing HashSet - PASSED\n");
}