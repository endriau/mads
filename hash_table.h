//
// Created by p0int3r on 6/13/21.
//

#ifndef TINYLIB_HASH_TABLE_H
#define TINYLIB_HASH_TABLE_H


#include "pair.h"
#include "uni_hash.h"


#define INITIAL_SIZE 107
#define CHAIN_LIST 76
#define CHAIN_TREE 84


typedef unsigned long long int lluint;

typedef lluint (*hash_table_hash_fn)(uni_hash_t *, const void *);


typedef struct
{
    void **A;
    int type;
    lluint n;
    lluint size;
    double lf;
    uni_hash_t *hfunc;
    hash_table_hash_fn hash;
} hash_table_t;


hash_table_t *hash_table_create(hash_table_hash_fn hash, int chain_type);
void hash_table_insert(hash_table_t *t, pair_t *p);
int hash_table_lookup(hash_table_t *t, void *key);
void hash_table_remove(hash_table_t *t, void *key);
void *hash_table_get_value(hash_table_t *t, void *key);
void hash_table_change_value(hash_table_t *t, void *key, void *value);
void hash_table_print(hash_table_t *t);
void hash_table_free(hash_table_t *t);


#endif //TINYLIB_HASH_TABLE_H
