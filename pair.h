//
// Created by p0int3r on 6/12/21.
//

#ifndef C_DATA_STRUCTURES_PAIR_H
#define C_DATA_STRUCTURES_PAIR_H


/*
 * This file contains data type definitions
 * and function prototypings regarding the
 * pair data structure that represents a
 * cue/value tuple.
 *
 * @author: Endri Kastrati
 * @date:   30/12/2016
 *
 */


typedef int (*cue_compare_fn)(const void *, const void *);
typedef void (*cue_print_fn)(const void *);
typedef void (*cue_destroy_fn)(void *);


typedef int (*value_compare_fn)(const void *, const void *);
typedef void (*value_print_fn)(const void *);
typedef void (*value_destroy_fn)(void *);


typedef struct
{
    void *cue;
    cue_compare_fn cmp;
    cue_print_fn print;
    cue_destroy_fn destroy;
} cue_t;


typedef struct
{
    void *value;
    value_compare_fn cmp;
    value_print_fn print;
    value_destroy_fn destroy;
} value_t;


typedef struct
{
    cue_t *k;
    value_t *v;
} pair_t;


cue_t *cue_create(void *cue, cue_compare_fn cmp, cue_print_fn print, cue_destroy_fn destroy);
void *cue_get(cue_t *k);
int cue_compare_to(cue_t *k, void *data);
void cue_print(cue_t *k);
void cue_free(cue_t *k);


value_t *value_create(void *value, value_compare_fn cmp, value_print_fn print, value_destroy_fn destroy);
void *value_get(value_t *v);
int value_compare_to(value_t *v, void *data);
void value_print(value_t *v);
void value_free(value_t *v);


pair_t *pair_create(cue_t *k,value_t *v);
cue_t *pair_get_cue(pair_t *p);
value_t *pair_get_value(pair_t *p);
void pair_change_cue(pair_t *p, cue_t *new_k);
void pair_change_value(pair_t *p, value_t *new_v);
void pair_print(pair_t *p);
void pair_free(pair_t *p);



#endif //C_DATA_STRUCTURES_PAIR_H
