//
// Created by p0int3r on 6/13/21.
//

#ifndef TINYLIB_CUCKOO_TABLE_H
#define TINYLIB_CUCKOO_TABLE_H


#include "pair.h"
#include "uni_hash.h"


#define INITIAL_CUCKOO_SIZE 53
#define MAX_LOOP_ITERATIONS 26

typedef unsigned long long int lluint;

typedef lluint (*cuckoo_hash_fn)(uni_hash_t *, const void *);


typedef struct
{
    void **T1;
    void **T2;
    lluint n;
    lluint size;
    double lf;
    uni_hash_t *hfunc1;
    uni_hash_t *hfunc2;
    cuckoo_hash_fn hash;
} cuckoo_table_t;


cuckoo_table_t *cuckoo_table_create(cuckoo_hash_fn hash);
void cuckoo_table_insert(cuckoo_table_t *c, pair_t *p);
int cuckoo_table_lookup(cuckoo_table_t *c, void *key);
void cuckoo_table_remove(cuckoo_table_t *c, void *key);
void *cuckoo_table_get_value(cuckoo_table_t *c, void *key);
void cuckoo_table_change_value(cuckoo_table_t *c, void *key, void *value);
void cuckoo_table_print(cuckoo_table_t *c);
void cuckoo_table_free(cuckoo_table_t *c);


#endif //TINYLIB_CUCKOO_TABLE_H
