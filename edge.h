//
// Created by p0int3r on 6/13/21.
//

#ifndef TINYLIB_EDGE_H
#define TINYLIB_EDGE_H


typedef int (*edge_compare_fn)(const void *, const void *);
typedef void (*edge_print_fn)(const void *);
typedef void (*edge_destroy_fn)(void *);


typedef struct
{
    void *weight;
    void *endpoint;
    edge_compare_fn cmp;
    edge_print_fn print;
    edge_destroy_fn destroy;
} edge_t;


edge_t *edge_create(void *w, void *ep, edge_compare_fn cmp, edge_print_fn print, edge_destroy_fn destroy);
void *edge_get_weight(edge_t *edge);
void *edge_get_end_point(edge_t *edge);
void edge_change_weight(edge_t *edge, void *new_w);
void edge_change_end_point(edge_t *edge, void *new_ep);
int edge_compare_to(edge_t *edge, void *data);
void edge_print(edge_t *edge);
void edge_free(edge_t *edge);


#endif //TINYLIB_EDGE_H
