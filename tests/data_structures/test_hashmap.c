//
// Created by danie on 30/05/2024.
//

#include <assert.h>
#include <memory.h>
#include "test_hashmap.h"
#include "../../coop/data_structures/hashmap.h"

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

void test_hashmap_creation() {
    // Test creation of hashmap
    Hashmap *map = hashmap_new(hashmap_int_dup, hashmap_naive_free, hashmap_int_comparer,
                               &default_hashmap_strategy, integer_hash);
    assert(map != NULL);

    assert(memcmp(map->strategy, &default_hashmap_strategy, sizeof(HashmapStrategy)) == 0);
    hashmap_free(&map);
    assert(map == NULL);
}

void test_hashmap_insertion_and_removal() {
    // Test insertion and removal of elements
    Hashmap *map = hashmap_new(hashmap_int_dup, hashmap_naive_free, hashmap_int_comparer, &default_hashmap_strategy,
                               integer_hash);
    assert(map != NULL);

    int data1 = 42;
    int data2 = 123;

    // Insertion
    assert(hashmap_insert(map, &data1));
    assert(hashmap_insert(map, &data2));

    // Check contains
    assert(hashmap_contains(map, &data1));
    assert(hashmap_contains(map, &data2));

    // Removal
    hashmap_remove(map, &data1);
    assert(!hashmap_contains(map, &data1));
    assert(hashmap_contains(map, &data2));

    hashmap_remove(map, &data2);
    assert(!hashmap_contains(map, &data2));

    hashmap_free(&map);
    assert(map == NULL);
}

void test_hashmap_contains() {
    // Test contains function
    Hashmap *map = hashmap_new(hashmap_int_dup, hashmap_naive_free, hashmap_int_comparer, &default_hashmap_strategy,
                               integer_hash);
    assert(map != NULL);

    int data1 = 42;
    int data2 = 123;

    // Insertion
    assert(hashmap_insert(map, &data1));
    assert(hashmap_insert(map, &data2));

    // Check contains
    assert(hashmap_contains(map, &data1));
    assert(hashmap_contains(map, &data2));

    // Check non-existent element
    int data3 = 456;
    assert(!hashmap_contains(map, &data3));

    hashmap_free(&map);
    assert(map == NULL);
}

void test_hashmap_insert_duplicate() {
    // Test insertion of duplicate element
    Hashmap *map = hashmap_new(hashmap_int_dup, hashmap_naive_free, hashmap_int_comparer, &default_hashmap_strategy,
                               integer_hash);
    assert(map != NULL);

    int data1 = 42;

    // Insertion
    assert(hashmap_insert(map, &data1));

    // Attempt to insert duplicate
    assert(hashmap_insert(map, &data1));

    hashmap_free(&map);
    assert(map == NULL);
}

void test_hashmap_remove_nonexistent() {
    // Test removal of non-existent element
    Hashmap *map = hashmap_new(hashmap_int_dup, hashmap_naive_free, hashmap_int_comparer, &default_hashmap_strategy,
                               integer_hash);
    assert(map != NULL);

    int data1 = 42;

    // Insertion
    assert(hashmap_insert(map, &data1));

    // Attempt to remove non-existent element
    int data2 = 123;
    hashmap_remove(map, &data2);

    // Verify original element still exists
    assert(hashmap_contains(map, &data1));

    hashmap_free(&map);
    assert(map == NULL);
}

void test_hashmap_resize_up() {
    // Test resizing up
    HashmapStrategy strategy = {0.1, 0.9, 2.0, 2}; // Initial length is 5
    Hashmap *map = hashmap_new(hashmap_int_dup, hashmap_naive_free, hashmap_int_comparer, &strategy, integer_hash);
    assert(map != NULL);

    // Insert elements to trigger resize up
    for (int i = 0; i <4; ++i) {
        int *data = malloc(sizeof(int));
        *data = i;
        assert(hashmap_insert(map, data));
    }

    // Verify length increased after resize up
    assert(map->length > 5);

    hashmap_free(&map);
}

void test_hashmap_resize_down() {
    // Test resizing down
    HashmapStrategy strategy = {0.5, 0.9, 2.0, 10}; // Initial length is 20
    Hashmap *map = hashmap_new(hashmap_int_dup, hashmap_naive_free, hashmap_int_comparer, &strategy, integer_hash);
    assert(map != NULL);

    // Insert elements to trigger resize down
    for (int i = 0; i < 15; ++i) {
        int *data = malloc(sizeof(int));
        *data = i;
        assert(hashmap_insert(map, data));
    }

    for (int i = 0; i < 10; ++i) {
        int *data = malloc(sizeof(int));
        *data = i;
        hashmap_remove(map, data);
    }

    // Verify length decreased after resize down
    assert(map->length < 20);

    hashmap_free(&map);
}

void test_hashmap(void) {
    printf("Testing Hashmap");
    test_hashmap_creation();
    test_hashmap_insertion_and_removal();
    test_hashmap_insert_duplicate();
    test_hashmap_contains();
    test_hashmap_remove_nonexistent();
    test_hashmap_resize_up();
    test_hashmap_resize_down();
    printf(" PASSED\n");
}