#ifndef MADS_DATA_STRUCTURES_PAIR_H
#define MADS_DATA_STRUCTURES_PAIR_H


#ifdef __cplusplus
extern "C" {
#endif


#include <mads_export.h>


typedef int (*mads_cue_compare_fn)(const void *, const void *);
typedef void (*mads_cue_print_fn)(const void *);
typedef void (*mads_cue_destroy_fn)(void *);


typedef int (*mads_value_compare_fn)(const void *, const void *);
typedef void (*mads_value_print_fn)(const void *);
typedef void (*mads_value_destroy_fn)(void *);


typedef struct
{
    void *cue;
    mads_cue_compare_fn cmp;
    mads_cue_print_fn print;
    mads_cue_destroy_fn destroy;
} mads_cue_t;


typedef struct
{
    void *value;
    mads_value_compare_fn cmp;
    mads_value_print_fn print;
    mads_value_destroy_fn destroy;
} mads_value_t;


typedef struct
{
    mads_cue_t *k;
    mads_value_t *v;
} mads_pair_t;


MADS_EXPORT mads_cue_t *mads_cue_create(void *cue, mads_cue_compare_fn cmp, mads_cue_print_fn print, mads_cue_destroy_fn destroy);
MADS_EXPORT void *mads_cue_get(const mads_cue_t *k);
MADS_EXPORT int mads_cue_compare_to(const mads_cue_t *k, const void *data);
MADS_EXPORT void mads_cue_print(const mads_cue_t *k);
MADS_EXPORT void cue_free(mads_cue_t *k);

MADS_EXPORT mads_value_t *mads_value_create(void *value, mads_value_compare_fn cmp, mads_value_print_fn print, mads_value_destroy_fn destroy);
MADS_EXPORT void *mads_value_get(const mads_value_t *v);
MADS_EXPORT int mads_value_compare_to(const mads_value_t *v, const void *data);
MADS_EXPORT void mads_value_print(const mads_value_t *v);
MADS_EXPORT void mads_value_free(mads_value_t *v);

MADS_EXPORT mads_pair_t *mads_pair_create(mads_cue_t *k, mads_value_t *v);
MADS_EXPORT mads_cue_t *mads_pair_get_cue(const mads_pair_t *p);
MADS_EXPORT mads_value_t *mads_pair_get_value(const mads_pair_t *p);
MADS_EXPORT void mads_pair_change_cue(mads_pair_t *p, mads_cue_t *new_k);
MADS_EXPORT void mads_pair_change_value(mads_pair_t *p, mads_value_t *new_v);
MADS_EXPORT void mads_pair_print(const mads_pair_t *p);
MADS_EXPORT void mads_pair_free(mads_pair_t *p);

#ifdef __cplusplus
}
#endif

#endif //MADS_DATA_STRUCTURES_PAIR_H
