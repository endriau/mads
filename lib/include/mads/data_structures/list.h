#ifndef MADS_DATA_STRUCTURES_LIST_H
#define MADS_DATA_STRUCTURES_LIST_H


typedef int (*mads_list_compare_fn)(const void *, const void *);
typedef void (*mads_list_print_fn)(const void *);
typedef void (*mads_list_destroy_fn)(void *);

typedef struct mads_llnode mads_llnode_t;

struct mads_llnode
{
    void *data;
    mads_llnode_t *next;
    mads_llnode_t *previous;
};


typedef struct
{
    unsigned long long int size;
    mads_llnode_t *head;
    mads_llnode_t *foot;
    mads_list_compare_fn cmp;
    mads_list_print_fn print;
    mads_list_destroy_fn destroy;
} mads_list_t;


mads_list_t *mads_list_create(mads_list_compare_fn cmp, mads_list_print_fn print, mads_list_destroy_fn destroy);
void mads_list_push(mads_list_t *list, void *data);
void mads_list_append(mads_list_t *list, void *data);
void mads_list_insert_at(mads_list_t *list, void *data, unsigned long long int position);
void *mads_list_get_head(const mads_list_t *list);
void *mads_list_get_foot(const mads_list_t *list);
void *mads_list_get_at(const mads_list_t *list, unsigned long long int position);
void mads_list_remove_head(mads_list_t *list);
void mads_list_remove_foot(mads_list_t *list);
void mads_list_remove_at(mads_list_t *list, unsigned long long int position);
void mads_list_print(const mads_list_t *list);
void mads_list_free(mads_list_t *list);
unsigned long long int mads_list_size(const mads_list_t *list);
int mads_list_is_empty(const mads_list_t *list);
int mads_list_has_elem(const mads_list_t *list, const void *item);


#endif //MADS_DATA_STRUCTURES_LIST_H
