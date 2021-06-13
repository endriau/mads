//
// Created by p0int3r on 6/12/21.
//

#ifndef C_DATA_STRUCTURES_UNI_HASH_H
#define C_DATA_STRUCTURES_UNI_HASH_H

typedef unsigned long long int lluint;

typedef struct
{
    lluint kvalue;
    lluint *values;
    lluint tabsize;
} uni_hash_t;


uni_hash_t *uni_hash_create(lluint ts, lluint k);
lluint *uni_hash_get_values(uni_hash_t *h);
lluint uni_hash_get_table_size(uni_hash_t *h);
lluint uni_hash_get_k(uni_hash_t *h);
void uni_hash_print(uni_hash_t *h);
void uni_hash_free(uni_hash_t *h);


#endif //C_DATA_STRUCTURES_UNI_HASH_H
